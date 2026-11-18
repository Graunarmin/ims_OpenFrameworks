/*
Project Description:
Johanna Sacher 2026
https://github.com/Graunarmin
Sources:
 Daniel Buzzo: https://github.com/danbz/art-and-code/blob/master/openFrameworks/music-for-homemade-airports/src/ofApp.cpp
 Sound Samples: https://reverbmachine.com/blog/deconstructing-brian-eno-music-for-airports
 To fix the OS-X Problem where ofGetSoundSpectrum was not implemented: https://forum.openframeworks.cc/t/ofsoundgetspectrum-not-implemented-on-this-platform-on-osx/45398/4
*/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	m_totalSampleCount = 8;
	m_sampleSpeed = 1;
	m_samplePan = 0;
	LoadSamples();
	
	m_showProgress = true;
	
	m_autoPlayOn = true;
	m_autoPlayTempo = 0;
	m_autoPlayMinTempo = 4000;
	m_autoPlayMaxTempo = 6000;
	
	m_currentTime = ofGetSystemTimeMillis();
	
	ofSetCircleResolution(100);
	
	m_visualizationIndex = 1;
	//ofSetBackgroundAuto(false); // the screen won't be cleared anymore if set to false
	ofEnableAlphaBlending(); //on by default?
	ofBackground(0, 0, 0);
	
	controller = RemoteControl();
	
	ofAddListener(controller.OnSpeedChanged, this, &ofApp::UpdateSpeedTo);
	ofAddListener(controller.OnPanChanged, this, &ofApp::UpdatePanTo);
	ofAddListener(controller.OnAutoPlayChanged, this, &ofApp::UpdateAutoPlayTo);
	ofAddListener(controller.OnNewSampleSelected, this, &ofApp::OnSampleTrackSelected);
	ofAddListener(controller.OnVisuStyleChanged, this, &ofApp::UpdateVisuStyleTo);
	
}

//--------------------------------------------------------------
// update() is always called before draw() so ... every frame I guess?
void ofApp::update()
{
	controller.Update();
	
	if(m_autoPlayOn)
	{
		AutoPlay();
	}
}

//--------------------------------------------------------------
// draw() is called after update()
void ofApp::draw()
{
	if(!ofGetBackgroundAuto())
	{
		FadeOutBackground();
	}
	
	ofSetColor(255);
	
	if(m_showProgress)
	{
		DrawProgressBars();
	}
	
	if(m_visualizationIndex == 1)
	{
		DrawSineWaveRadiusSpectrum();
	}
	else if(m_visualizationIndex == 2)
	{
		DrawSineWaveColorSpectrum();
	}
	else
	{
		DrawFrequencyWheel();
	}

}

//--------------------------------------------------------------
void ofApp::exit()
{
	std::cout << "Removing Listeners ... " << std::endl;
	ofRemoveListener(controller.OnPanChanged, this, &ofApp::UpdatePanTo);
	ofRemoveListener(controller.OnSpeedChanged, this, &ofApp::UpdateSpeedTo);
	ofRemoveListener(controller.OnAutoPlayChanged, this, &ofApp::UpdateAutoPlayTo);
	ofRemoveListener(controller.OnNewSampleSelected, this, &ofApp::OnSampleTrackSelected);
	ofRemoveListener(controller.OnVisuStyleChanged, this, &ofApp::UpdateVisuStyleTo);
	
	std::cout << "Exiting Application" << std::endl;
}

// ---- SAMPLE MANAGEMENT: LOADING & PLAYING ---
void ofApp::LoadSamples()
{
	m_samples.clear();
	
	for(int i = 0; i < m_totalSampleCount; i++)
	{
		ofSoundPlayer sample;
		m_samplePath = std::format("Piano_cut/Eno-Piano-0{}_cut.wav", i+1);
		std::cout << "loading " << m_samplePath << std::endl;
		sample.load(m_samplePath);
		sample.setMultiPlay(true); //MultiPlay allows for multiple instances of the same sample to play at the same time, so you can start the same sample again, even while another instance of it is still playing.
		m_samples.push_back(sample);
	}
}

void ofApp::PlaySampleAt(int index)
{
	std::cout << "Playing Sample at " << index + 1 << std::endl;
	if(m_samples.size() >= index + 1)
	{
		auto sample = m_samples[index];
		sample.setSpeed(m_sampleSpeed);
		sample.setPan(m_samplePan);
		sample.play();
	}
	else
	{
		std::cout << index << " is not a valid sample in the current selection";
	}
}

void ofApp::OnSampleTrackSelected(int &buttonNumber)
{
	PlaySampleAt(buttonNumber-1);
}

// ---- HELP & DEBUG
void ofApp::DrawProgressBars()
{
	for (int i = 0; i < m_totalSampleCount; i++) {
		if(m_samples[i].isPlaying())
		{
			ofDrawRectangle(90, (i*20) + 7, //starting point x,y
							ofMap(m_samples[i].getPosition(), 0, 1, 20, ofGetWidth()-110), //width
							18); //height
			ofDrawBitmapStringHighlight("sample " + ofToString(i + 1 ) + ":",
										10, (i+1) * 20);
		}
		else
		{
			ofDrawBitmapString("sample " + ofToString(i + 1 ) + ":",
							   10, (i+1) * 20);
		}
	}
	WriteHelpText();
}

void ofApp::WriteHelpText()
{
	ofDrawBitmapString("Toggle help with 'g'", 10, 200);
	ofDrawBitmapString("Toggle Autoplay with 'a'", 10, 220);
	if(m_autoPlayOn)
	{
		ofDrawBitmapString("Auto play is ON", 10, 240);
		ofDrawBitmapString("Next Sample in " + ofToString(((m_currentTime + m_autoPlayTempo) - ofGetSystemTimeMillis())/1000), 10, 260);
	}
	else
	{
		ofDrawBitmapString("Auto play is OFF", 10, 240);
	}
	ofDrawBitmapString("Speed for next sample is " + ofToString(m_sampleSpeed), 10, 300);
	ofDrawBitmapString("Pan for next sample is " + ofToString(m_samplePan), 10, 320);
}
	
// ---- AUTO PLAY ----
void ofApp::AutoPlay()
{
	if(ofGetSystemTimeMillis() > m_currentTime + m_autoPlayTempo)
	{
		m_nextSampleIndex = ofRandom(m_totalSampleCount);
		PlaySampleAt(m_nextSampleIndex);
		m_currentTime = ofGetSystemTimeMillis();
		auto tempoModifier = m_sampleSpeed * (-2000) + 2000;
		m_autoPlayTempo = ofRandom(m_autoPlayMinTempo + tempoModifier, m_autoPlayMaxTempo + tempoModifier);
	}
}

void ofApp::UpdateAutoPlayTo(bool &newValue)
{
	m_autoPlayOn = newValue;
}

void ofApp::ToggleAutoPlay()
{
	m_autoPlayOn = !m_autoPlayOn;
	controller.SendAutoPlayChangeFeedback(m_autoPlayOn);
}

// ---- SPEED ----
void ofApp::UpdateSpeedBy(float amount)
{
	m_sampleSpeed += amount;
	controller.SendSpeedChangeFeedback(m_sampleSpeed);
}
void ofApp::UpdateSpeedTo(float &newSpeed)
{
	m_sampleSpeed = newSpeed;
}

// ---- PAN ----

void ofApp::UpdatePanBy(float amount)
{
	m_samplePan += amount;
	controller.SendPanChangeFeedback(m_samplePan);
}
void ofApp::UpdatePanTo(float &newPan)
{
	m_samplePan = newPan;
}


// ---- VISUALIZATION ----
void ofApp::UpdateVisuStyleTo(int &index)
{
	m_visualizationIndex = index;
	if(index == 1 || index == 2){
		ofSetBackgroundAuto(true);
	}
	else
	{
		ofSetBackgroundAuto(false);
	}
}

void ofApp::UpdateVisuStyleTo(int index)
{
	m_visualizationIndex = index;
	if(index == 1 || index == 2){
		ofSetBackgroundAuto(true);
	}
	else
	{
		ofSetBackgroundAuto(false);
	}
	controller.SendVisuChangeFeedback(m_visualizationIndex);
}

void ofApp::FadeOutBackground()
{
	ofSetColor(0, 0, 0, 38);
	//ofFill();
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
}

void ofApp::DrawFrequencyWheel()
{
	float bandsToGet = 512;
	//float exactBarWidth = (2 * acos(0.0) * 50) / bandsToGet;
	float barWidth = 40;
	int barLength = 400;
	
	auto val = ofSoundGetSpectrum(bandsToGet);
	
	for(int i = 0; i < bandsToGet; i++)
	{
		// mapping sound to color isn't as easy as I thought. Maybe later.
		//ofDrawRectangle(100 + i * width, ofGetHeight()-100, width, -(val[i] * 200));
		
		ofPushMatrix();
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2); // translate the origin to the middle of the window
		ofRotateDeg(360/bandsToGet * i); // rotate around the (newly set) origin
		
		ofColor drawingColor;
		drawingColor.setHsb(255/bandsToGet * i, 255, 255, 50);
		ofSetColor(drawingColor);
		ofDrawRectangle(50, -barWidth/2, val[i] * barLength, barWidth/2);
		
		ofPopMatrix();
	}
}

void ofApp::DrawSineWaveRadiusSpectrum()
{
	float time = ofGetElapsedTimef();
	int bandsToGet = 512;
	auto val = ofSoundGetSpectrum(bandsToGet);
	auto screenHeight = ofGetHeight();
	
	int circlesPerBand = glm::ceil(screenHeight/bandsToGet) + 1;
	bool evenNumberOfCircles = circlesPerBand % 2 == 0;
	int halfTheCircles = glm::floor(circlesPerBand/2);
	int stepsToMiddle = glm::ceil(circlesPerBand / 2);
	
	int bandCounter = 0;
	
	for(int x = 0; x < 1; x++)
	{
		for(int p = 0; p < screenHeight; p += circlesPerBand)
		{
			auto shiftedIndex = (bandCounter - bandsToGet/5) % bandsToGet;
			
			for (int i = 0; i < circlesPerBand; i++)
			{
				ofSetColor(127 + 127 * sin((p+i) * 0.02 + time),
						   127 + 127 * sin((p+i) * 0.021 + time),
						   127 + 127 * sin((p+i) * 0.022 + time));
				
				// Interpolation between the radii so the change is a bit smoother
				float lerpedRadius;
				
				if(!evenNumberOfCircles)
				{
					float step = ((i % stepsToMiddle) + 1) / stepsToMiddle;
					if(i < halfTheCircles)
					{
						lerpedRadius = ofLerp(val[shiftedIndex-1], val[shiftedIndex], step);
					}
					else if(i > halfTheCircles)
					{
						lerpedRadius = ofLerp(val[shiftedIndex], val[shiftedIndex + 1], step);
					}
					else
					{
						lerpedRadius = val[shiftedIndex];
					}
				}
				else
				{
					if(i < halfTheCircles -1)
					{
						lerpedRadius = ofLerp(val[shiftedIndex - 1], val[shiftedIndex], (i+1) / stepsToMiddle);
					}
					else if(i > halfTheCircles + 1)
					{
						lerpedRadius = ofLerp(val[shiftedIndex], val[shiftedIndex + 1], (i % stepsToMiddle) / stepsToMiddle);
					}
					else
					{
						lerpedRadius = val[shiftedIndex];
					}
				}
				
				/*ofDrawCircle(ofGetWidth()/2 + 100 * sin((p + i) * 0.01 + time),
							 (p + i),
							 50 + 30 * sin((p + i) * 0.005 + time));*/
				
				/*ofDrawCircle(ofGetWidth()/2 + 100 * sin((p + i) * 0.01 + time + x),
							 (p + i),
							 50 + 30 * sin((p + i) * 0.005 + time + x));*/
				
				ofDrawCircle(ofGetWidth()/2 + 100 * sin((p + i) * 0.01 + time + x),
							 (p + i),
							 50 + 10 * sin((lerpedRadius * bandCounter) * 0.2 + time + x));
			}
			bandCounter += 1;
		}
	}
}

void ofApp::DrawSineWaveColorSpectrum()
{
	float time = ofGetElapsedTimef();
	int bandsToGet = 512;
	auto val = ofSoundGetSpectrum(bandsToGet);
	auto screenHeight = ofGetHeight();
	
	int circlesPerBand = glm::ceil(screenHeight/bandsToGet) + 1;
	bool evenNumberOfCircles = circlesPerBand % 2 == 0;
	int halfTheCircles = glm::floor(circlesPerBand/2);
	int stepsToMiddle = glm::ceil(circlesPerBand / 2);
	
	int bandCounter = 0;
	
	for(int x = 0; x < 3; x++)
	{
		for(int p = 0; p < screenHeight; p += circlesPerBand)
		{
			auto shiftedIndex = (bandCounter - bandsToGet/4) % bandsToGet;
			
			for (int i = 0; i < circlesPerBand; i++)
			{
				
				ofSetColor(127 + 127 * sin(bandCounter * (val[shiftedIndex] + 0.01) + time),
				 127 + 127 * sin(bandCounter * (val[shiftedIndex] + 0.011) + time),
				 127 + 127 * sin(bandCounter * (val[shiftedIndex] + 0.012) + time));
				
				
				
				/*ofDrawCircle(ofGetWidth()/2 + 100 * sin((p + i) * 0.01 + time),
							 (p + i),
							 50 + 30 * sin((p + i) * 0.005 + time));*/
				
				ofDrawCircle(ofGetWidth()/2 + 100 * sin((p + i) * 0.01 + time + x*10),
							 (p + i),
							 50 + 30 * sin((p + i) * 0.005 + time + x));
				
			}
			bandCounter += 1;
		}
	}
}


//---------------- OF EVENTS -------------------
void ofApp::keyPressed(int key)
{
	switch (key) {
		case 'f':
			ofToggleFullscreen();
			break;
			
		case '1':
			PlaySampleAt(0);
			break;
		case '2':
			PlaySampleAt(1);
			break;
		case '3':
			PlaySampleAt(2);
			break;
		case '4':
			PlaySampleAt(3);
			break;
		case '5':
			PlaySampleAt(4);
			break;
		case '6':
			PlaySampleAt(5);
			break;
		case '7':
			PlaySampleAt(6);
			break;
		case '8':
			PlaySampleAt(7);
			break;
		case '9':
			PlaySampleAt(8);
			break;
		
		case 'a':
			ToggleAutoPlay();
			break;
		case 'g':
			m_showProgress = !m_showProgress;
			break;
			
		case 'w':
			UpdateVisuStyleTo(0);
			break;
		case 's':
			UpdateVisuStyleTo(1);
			break;
		case 'c':
			UpdateVisuStyleTo(2);
			break;
			
		case OF_KEY_LEFT:
			if(m_samplePan > -1.0f)
			{
				UpdatePanBy(-0.1f);
			}
			break;
		case OF_KEY_RIGHT:
			if(m_samplePan < 1.0f)
			{
				UpdatePanBy(0.1f);
			}
			break;
		case OF_KEY_UP:
			if(m_sampleSpeed < 2.0f)
			{
				UpdateSpeedBy(0.1f);
			}
			break;
		case OF_KEY_DOWN:
			if(m_sampleSpeed > 0.1)
			{
				UpdateSpeedBy(-0.1f);
			}
			break;
			
		default:
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
