#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include "glm/gtc/type_ptr.hpp"
#include "../sources/engine/graphics/shader_program.h"
#include "../sources/engine/graphics/camera.h"
#include "../sources/engine/graphics/model.h"
#include "../sources/engine/graphics/renderer_2d.h"
#include "../sources/scenes/ui_contol_panel.h"
#include "../sources/engine/graphics/skybox.h"


/* This assignment's scene. */
class MainScene final: public IGameScene
{
public:
	void onStart() override {
		// vertex and fragment shaders for rendering 3d models
		program = new ShaderProgram("shaders/basic.vs", "shaders/basic.fs");
		program->compileAndLink();

		//keyboard pointer
		keyboard = Input::getKeyboard();

		//renderer for text and sprites
		renderer2d = new Renderer2D(Dimension2D(Game::WIDTH, Game::HEIGHT), "sprite2d");

		//creates a 3d camera with starting position and direction
		camera = new Camera(Game::WIDTH, Game::HEIGHT);
		camera->setPosition(glm::vec3(7.0f, 10.0f, -15.0f));
		camera->lookAtPoint(glm::vec3(0.0f, 2.0f, 1.0f));

		//randomly select from 7 included textures for draco model
		std::srand((unsigned) time(nullptr));
		auto textureIndex = (std::rand() % 6) + 1;
		auto textureName = "assets/draco/draco" + std::to_string(textureIndex) + ".png";

		//main character
		draco = new Model("assets/draco/draco.obj", textureName);
		draco->getTransform().scale(3.0f);

		//island model
		island = new Model("assets/island/island.obj", "assets/island/island_ground.png");
		island->getTransform().moveBy(0.0f, -25.0f, 0.0f);

		//user interface panel
		panel = new UIControlPanel(draco);

		//vector of cubemap faces' textures
		std::vector<std::string> faces;
		faces.push_back("assets/skybox/corona_rt.png");
		faces.push_back("assets/skybox/corona_lf.png");
		faces.push_back("assets/skybox/corona_up.png");
		faces.push_back("assets/skybox/corona_dn.png");
		faces.push_back("assets/skybox/corona_bk.png");
		faces.push_back("assets/skybox/corona_ft.png");

		//skybox 
		skybox = new Skybox(faces, "shaders/skybox");
	}

	virtual void onUpdate(double dt) override {
		//restore camera
		if (keyboard->isKeyPressed(GLFW_KEY_C)) {
			camera->setPosition(glm::vec3(7.0f, 10.0f, -15.0f));
			camera->lookAtPoint(glm::vec3(0.0f, 2.0f, 1.0f));
		}
		
		//update() functions called every frame
		camera->update(dt);
		panel->update();
	}

	void onRender() override {
		//clear the screen and depth buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//bind shader program
		program->use();

		//get view and projection matrices from camera
		glm::mat4 view = camera->getViewMatrix();
		glm::mat4 projection = camera->getProjectionMatrix();

		//set uniforms 
		GLint viewLoc = glGetUniformLocation(program->getID(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		GLint projLoc = glGetUniformLocation(program->getID(), "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//draw calls for draco, ground and skybox
		island->render(*program);
		draco->render(*program);
		skybox->render(*camera);

		//2d stuff 
		panel->render(*renderer2d);
	}

	void onClose() override {
		delete program;
		delete camera;
		delete draco;
		delete renderer2d;
		delete panel;
		delete skybox;
	}

private:
	ShaderProgram* program; 
	Camera* camera;
	Model* island;
	Model* draco;
	Renderer2D* renderer2d;
	UIControlPanel* panel;
	Skybox* skybox;
	Keyboard* keyboard;
};

#endif
