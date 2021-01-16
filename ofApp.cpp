#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	int radius = 50;
	int outer_deg = 0;
	ofSeedRandom(39);

	this->line.clear();

	for (int x = 72; x <= ofGetWidth(); x += 144) {

		for (int y = 72; y <= ofGetWidth(); y += 144) {

			glm::vec3 noise_seed(ofRandom(1000), ofRandom(1000), ofRandom(1000));
			outer_deg += 90;
			for (int deg = 0; deg < 360; deg += 5) {

				this->line.addVertex(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
				this->line.addVertex(glm::vec3(radius * 0.5 * cos(deg * DEG_TO_RAD), radius * 0.5 * sin(deg * DEG_TO_RAD), 0));

				auto angle_x = ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.005), 0, 1, -PI, PI);
				auto angle_y = ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * 0.005), 0, 1, -PI, PI);
				auto angle_z = ofMap(ofNoise(noise_seed.z, ofGetFrameNum() * 0.005), 0, 1, -PI, PI);
				auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
				auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
				auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));

				float outer_angle_x = outer_deg * DEG_TO_RAD;
				auto outer_rotationx_x = glm::rotate(glm::mat4(), outer_angle_x, glm::vec3(1, 0, 0));

				this->line.setVertex(this->line.getNumVertices() - 2,
					glm::vec3(x, y, 0) + glm::vec4(this->line.getVertex(this->line.getNumVertices() - 2), 0) * outer_rotationx_x);
				this->line.setVertex(this->line.getNumVertices() - 1,
					glm::vec3(x, y, 0) + glm::vec4(this->line.getVertex(this->line.getNumVertices() - 1), 0) * rotation_z * rotation_y * rotation_x);

				this->line.addIndex(this->line.getNumVertices() - 2);
				this->line.addIndex(this->line.getNumVertices() - 1);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->line.draw();

	for (auto& vertex : this->line.getVertices()) {

		ofDrawSphere(vertex, 1);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}