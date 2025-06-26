#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	float span = 1;
	for (float x = 0; x < ofGetWindowWidth(); x += span) {

		for (float y = 0; y < ofGetWindowHeight(); y += span) {

			auto len = glm::distance(glm::vec2(x, y), ofGetWindowSize() * 0.5);
			auto noise_value = ofMap(ofNoise(len * 0.01 + ofGetFrameNum() * 0.1, x * 0.01, y * 0.01), 0, 1, 0, 12);
			if ((int)noise_value % 2 == 0) {

				continue;
			}

			this->mesh.addVertex(glm::vec3(x, y, 0));
			this->mesh.addVertex(glm::vec3(x + span, y, 0));
			this->mesh.addVertex(glm::vec3(x + span, y + span, 0));
			this->mesh.addVertex(glm::vec3(x, y + span, 0));

			this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 4); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
			this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);

			auto alpha = len < 50 ? 255 : len < 250 ? ofMap(len, 50, 250, 255, 0) : ofMap(len, 250, 350, 0, 255);

			for (int i = 0; i < 4; i++) {

				this->mesh.addColor(ofColor(255, alpha));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->mesh.draw();

	/*
	int start = 25;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}