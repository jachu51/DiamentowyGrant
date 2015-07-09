package org.dg.openAIL;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.Scanner;
import java.util.Timer;
import java.util.TimerTask;

import org.dg.camera.VisualPlaceRecognition;
import org.dg.graphManager.GraphManager;
import org.dg.graphManager.wiFiMeasurement;
import org.dg.inertialSensors.InertialSensors;
import org.dg.wifi.WiFiPlaceRecognition.IdPair;
import org.dg.wifi.MyScanResult;
import org.dg.wifi.WifiScanner;
import org.xmlpull.v1.XmlPullParserException;

import android.hardware.SensorManager;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import android.os.Environment;
import android.util.Log;

// This is a class that is supposed to provide the interface for all available solutions
public class OpenAndroidIndoorLocalization {
	private static final String moduleLogName = "OpenAIL";
	
	
	
	// Parameters
	static boolean WiFiFeatures = true;
	ConfigurationReader.Parameters parameters;

	// Inertial sensors
	public SensorManager sensorManager;
	public InertialSensors inertialSensors;

	// WiFi
	public WifiScanner wifiScanner;
	int detectWiFiIssue;
	
	// Visual Place Recognition
	public VisualPlaceRecognition visualPlaceRecognition;

	// Graph
	public GraphManager graphManager;

	// Graph update
	private Timer updateGraphTimer = new Timer();

	public OpenAndroidIndoorLocalization(SensorManager sensorManager,
			WifiManager wifiManager) {
		
		// Create directory if it doesn't exist
				File folder = new File(Environment.getExternalStorageDirectory()
						+ "/OpenAIL/PriorData/");

				if (!folder.exists()) {
					folder.mkdir();
				}

		// Reading settings
		parameters = readParametersFromXML("settings.xml");
		
		// Init graph
		graphManager = new GraphManager(parameters.graphManager);

		// Init inertial sensors
		if ( parameters.inertialSensors.useModule )
			inertialSensors = new InertialSensors(sensorManager);

		// Init WiFi
		wifiScanner = new WifiScanner(wifiManager, parameters.wifiPlaceRecognition);
		
	}

	public void initAfterOpenCV() {
		Log.d(moduleLogName, "Initializing OpenAIL submodules after OpenCV initialization");
		
		// Init Visual Place Recognition
		visualPlaceRecognition = new VisualPlaceRecognition();
	}

	public void startGraph() {
		graphManager.start();
		
		// Load WiFi place recognition database
		if (parameters.wifiPlaceRecognition.usePriorDatabase)
		{
			loadWiFiPlaceDatabase(parameters.wifiPlaceRecognition.priorDatabaseFile);
		}
		
		wifiScanner.startNewPlaceRecognitionThread();

		updateGraphTimer.scheduleAtFixedRate(new UpdateGraph(), 1000, 200);
		detectWiFiIssue = 0;
		graphManager.optimize(5);
	}

	public void stopAndOptimizeGraph() {
		updateGraphTimer.cancel();
		wifiScanner.stopNewPlaceRecognitionThread();

		graphManager.stop();
		graphManager.stopOptimizationThread();
		//graphManager.optimize(100);
		// TESTING GET POSITION
		graphManager.getVertexPosition(0);
		graphManager.getPositionsOfVertices();
	}

	private void loadWiFiPlaceDatabase(String filename) {
		// Reading database
		String readFileName = String.format(Locale.getDefault(), Environment
				.getExternalStorageDirectory().toString()
				+ "/OpenAIL/PriorData/"
				+ filename);

		try {
			Scanner placeDatabaseScanner = new Scanner(new BufferedReader(
					new FileReader(readFileName)));
			placeDatabaseScanner.useLocale(Locale.US);

			int id = 5000;
			while (placeDatabaseScanner.hasNext()) {
				float X = placeDatabaseScanner.nextFloat();
				float Y = placeDatabaseScanner.nextFloat();
				float Z = placeDatabaseScanner.nextFloat();
				int wifiCount = placeDatabaseScanner.nextInt();

				Log.d(moduleLogName, "WiFiDatabase 1st line: " + id + " " + X + " " + Y
						+ " " + Z + " " + wifiCount);
				String dummy = placeDatabaseScanner.nextLine();

				List<MyScanResult> wifiScan = new ArrayList<MyScanResult>();
				for (int i = 0; i < wifiCount; i++) {
					String line = placeDatabaseScanner.nextLine();
					
					
					String[] values = line.split("\\t+");

					String BSSID = values[0];
					int level;
					if ( values.length == 3)
						level = Integer.parseInt(values[2]);
					else 
						level = Integer.parseInt(values[1]);
					
					MyScanResult scan = new MyScanResult(BSSID, level);
					wifiScan.add(scan);
					
					Log.d(moduleLogName, "WiFiDatabase data: " + BSSID + " " + level);
				}

				// Adding to graph
				graphManager.addWiFiPlaceRecognitionVertex(id, X, Y, Z);

				// Add new scan to datbase
				wifiScanner.addScanToRecognition(id, wifiScan);
				
				id++;
			}
			placeDatabaseScanner.close();

		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	
	/*
	 * Method used to save last WiFi scan with wanted position (X,Y,Z) in a file
	 * that can be used as prior map
	 */
	public void saveWiFiMapPoint(double posX, double posY, double posZ, String fileName) {
		// Getting the last WiFi scan
		List<MyScanResult> wifiList = wifiScanner.getLastScan();
		
		// File to save results
		String pathName = "";
		pathName = String.format(Locale.getDefault(), Environment
				.getExternalStorageDirectory().toString()
				+ "/OpenAIL/PriorData/" + fileName);
		FileOutputStream foutStream;
		PrintStream outStreamRawData = null;
		try {
			foutStream = new FileOutputStream(pathName, true);
			outStreamRawData = new PrintStream(foutStream);
		} catch (FileNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		// Save the initial line of scan (posX, posY, posZ, number of WiFi networks)
		outStreamRawData.print(posX + " " + posY + " " + posZ + " " + wifiList.size()
				+ "\n");
		
		// Save BSSID (MAC), SSID (network name), lvl (in DBm)
		for (int i = 0; i < wifiList.size(); i++) {
			MyScanResult scanResult = wifiList.get(i);
			outStreamRawData.print(scanResult.BSSID + "\t" + scanResult.networkName + "\t" + scanResult.level
					+ "\n");
		}
		
		// Close stream
		outStreamRawData.close();
	}
	
	class UpdateGraph extends TimerTask {
		public void run() {
			
			// get distance
			double distance = inertialSensors.getGraphStepDistance();

			// Adding WiFi measurement
			if (distance > 0.01) {
				// get angle from our estimation
				// TODO: RIGHT NOW WE USE ANDROID ORIENTATION
				float yawZ = inertialSensors.getYawForStepometer();

				// We need to change yawZ into radians and change direction
				yawZ = (float) (-yawZ * Math.PI / 180.0f);

				graphManager.addStepometerMeasurement(distance, yawZ);
			}

			// Check if there is new measurement
			if (wifiScanner.isNewMeasurement()) {
				// All ok 
				detectWiFiIssue = 0;
				
				// New measurement had been read
				wifiScanner.newMeasurement(false);

				// WiFi place recognition
				int currentPoseId = graphManager.getCurrentPoseId();
				wifiScanner.setGraphPoseId(currentPoseId);

				// Find all matching places
				
				List<IdPair<Integer, Integer>> recognizedPlaces = wifiScanner
						.getRecognizedPlacesList();
				Log.d(moduleLogName, "The placeRecognition thread found "
						+ recognizedPlaces.size() + " connections");

				// Add new pose to search
				wifiScanner.addLastScanToRecognition(currentPoseId);

				// Add found results to the final graph
				// graphManager.addMultipleWiFiFingerprints(placesIds);
				graphManager.addMultipleWiFiFingerprints(recognizedPlaces);

				// TODO!!!!!!
				// TEMPORAILY DISABLED OPTIMIZATION WITH WIFI FEATURES (BUT
				// STILL SAVE TO FILE)
				if (WiFiFeatures) {
					// Adding WiFi measurements
					List<wiFiMeasurement> wifiList = wifiScanner
							.getGraphWiFiList();
//					if (wifiList != null)
//						graphManager.addMultipleWiFiMeasurements(wifiList);
				}
			} else if (wifiScanner.getRunningState()) {

				detectWiFiIssue++;

				// Bad scan received - need to restart
				if (detectWiFiIssue > 40) {
					Log.d(moduleLogName,
							"Restarting WiFi due to continuous scan issue");
					wifiScanner.startScanning();
				}

			}

		}

	}
	
	/**
	 * 
	 */
	private ConfigurationReader.Parameters readParametersFromXML(String fileName) {
		String configFileName = String.format(Locale.getDefault(), Environment
				.getExternalStorageDirectory().toString()
				+ "/OpenAIL"
				+ "/" + fileName);
		
		ConfigurationReader configReader = new ConfigurationReader();
		
		try {
			ConfigurationReader.Parameters params = configReader.readParameters(configFileName);
			return params;
		} catch (XmlPullParserException e) {
			Log.e(moduleLogName, "Failed to parse the config file");
		} catch (IOException e) {
			Log.e(moduleLogName, "Missing config file");
		}
		return null;
	}

}
