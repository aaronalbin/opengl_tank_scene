#include "Renderer.h"

namespace openGLDriver {

	Renderer::Renderer() {
	}

	Renderer::~Renderer() {
	}

	void Renderer::handleDisplay(SceneManager& scene) {
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.2,0.2,0.2,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		std::stack<glm::mat4> mv;

		glm::mat4 projection = glm::perspective(60.0f, 1.0f, .1f, 100.0f);
		glm::mat4 view = glm::lookAt(glm::vec3(0.0, 3.2, 5.0), 
					 	 glm::vec3(0.0, 0.0, 0.0),
						 glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 model = glm::mat4(1.0f);

		model = scene.getTrackball().getModelState();

		if (scene.getTrackball().getTrackballMove()) {
			model = glm::rotate(model, scene.getTrackball().getAngle(), scene.getTrackball().getAxis());
			scene.getTrackball().setModelState(model);
		}

		glm::vec4 lightPosition = glm::vec4(5.0, 75.0, 0.0, 1.0);
		drawCubeMap(scene, view, model, projection, lightPosition, mv);

		drawReflectSphere(scene, view, model, projection, lightPosition, mv);

		// draw floor with stencil value 3
		
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 3, 0xffffffff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		
		drawFloor(scene, view, model, projection, lightPosition, mv);  // floor is drawn with stencil enabled

		drawSU(scene, view, model, projection, lightPosition, mv);(scene, view, model, projection, lightPosition, mv);

		drawSUShadow(scene, view, model, projection, lightPosition, mv);  // utilizes stencil used in drawFloor()

		glDisable(GL_STENCIL_TEST);
		
		glFlush();
		glutSwapBuffers();
		
		/*
		GLenum err;
		while ( ( err = glGetError() ) != GL_NO_ERROR) {
			std::cerr << err;        
		}
		*/
		
	}

	void Renderer::drawFloor(SceneManager& scene, glm::mat4& view, glm::mat4& model, glm::mat4& projection, glm::vec4& lightPosition, std::stack<glm::mat4>& mv) {

		mv.push(model);
		model = glm::mat4(1.0f);
		glUseProgram(scene.getEmptyShader().getProgramObject());

		if (scene.getWireframe()) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// draw as wireframe
		}

		GLuint v0 = glGetAttribLocation(scene.getEmptyShader().getProgramObject(), "vertexPosition");
		GLuint v1 = glGetAttribLocation(scene.getEmptyShader().getProgramObject(), "vertexNormal");
		
		GLuint m0 = glGetUniformLocation(scene.getEmptyShader().getProgramObject(), "modelViewMatrix");
		GLuint m1 = glGetUniformLocation(scene.getEmptyShader().getProgramObject(), "normalMatrix");
		GLuint m2 = glGetUniformLocation(scene.getEmptyShader().getProgramObject(), "MVP");
		
		GLuint c0 = glGetUniformLocation(scene.getEmptyShader().getProgramObject(), "ambientColor");
		GLuint c1 = glGetUniformLocation(scene.getEmptyShader().getProgramObject(), "diffuseColor");
		GLuint c2 = glGetUniformLocation(scene.getEmptyShader().getProgramObject(), "specularColor");
		GLuint c3 = glGetUniformLocation(scene.getEmptyShader().getProgramObject(), "shininess");
		GLuint c4 = glGetUniformLocation(scene.getEmptyShader().getProgramObject(), "lightPosition");
		
		
		glEnableVertexAttribArray(v0);
		glEnableVertexAttribArray(v1);

		glBindBuffer(GL_ARRAY_BUFFER, scene.getFloorVBOHandle());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scene.getFloorVBOIndex());

		glVertexAttribPointer(v0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof( float ) * 0));
	    glVertexAttribPointer(v1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof( float ) * 4));
		
		model = glm::translate(model, glm::vec3(0.0, -2.5, 0.0));
		model = glm::scale(model, glm::vec3(10.0, 0.02, 10.0));

		glm::mat4 modelview = view * model;
		glm::mat4 normal = glm::transpose(glm::inverse(modelview));
		glm::mat4 modelview_projection = projection * modelview;

		// pass the matrix to the shader as a uniform
		glUniformMatrix4fv(m0, 1, GL_FALSE, glm::value_ptr(modelview));
		glUniformMatrix4fv(m1, 1, GL_FALSE, glm::value_ptr(normal));
		glUniformMatrix4fv(m2, 1, GL_FALSE, glm::value_ptr(modelview_projection));

		glUniform3fv(c0, 1, glm::value_ptr(scene.getFloor().getAmbientColor()));
		glUniform3fv(c1, 1, glm::value_ptr(scene.getFloor().getDiffuseColor()));
		glUniform3fv(c2, 1, glm::value_ptr(scene.getFloor().getSpecularColor()));
		glUniform1f(c3, scene.getFloor().getShininess());
		glUniform4fv(c4, 1, glm::value_ptr(lightPosition));

		glDrawElements(GL_TRIANGLES, scene.getFloor().getNumIndices(), GL_UNSIGNED_INT, (GLvoid*)0);

		model = mv.top();  mv.pop();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// restore default polygon mode

		glDisableClientState(v0);
        glDisableClientState(v1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}

	void Renderer::drawSU(SceneManager& scene, glm::mat4& view, glm::mat4& model, glm::mat4& projection, glm::vec4& lightPosition, std::stack<glm::mat4>& mv) {
		
		mv.push(model);
		model = glm::mat4(1.0f);
		glUseProgram(scene.getBumpShader().getProgramObject());

		if (scene.getWireframe()) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// draw as wireframe
		}

		// send color texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, scene.getSUTextureHandle());
		GLuint uniloc = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "tex");
		if (uniloc >= 0) {
			glUniform1i(uniloc, 0);
		}

		// send normal texture
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, scene.getSUTextureNormalHandle());
		GLuint uniloc2 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "tex2");
		if (uniloc2 >= 0) {
			glUniform1i(uniloc2, 1);
		}

		GLuint v0 = glGetAttribLocation(scene.getBumpShader().getProgramObject(), "vertexPosition");
		GLuint v1 = glGetAttribLocation(scene.getBumpShader().getProgramObject(), "vertexNormal");
		GLuint v2 = glGetAttribLocation(scene.getBumpShader().getProgramObject(), "vertexTexture");
		GLuint v3 = glGetAttribLocation(scene.getBumpShader().getProgramObject(), "vertexTangent");
		
		GLuint m0 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "modelViewMatrix");
		GLuint m1 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "normalMatrix");
		GLuint m2 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "MVP");

		GLuint m3 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "projection");
		GLuint m4 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "view");
		GLuint m5 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "model");
		
		GLuint c0 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "ambientColor");
		GLuint c1 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "diffuseColor");
		GLuint c2 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "specularColor");
		GLuint c3 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "shininess");
		GLuint c4 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "lightPosition");
		
		glEnableVertexAttribArray(v0);
		glEnableVertexAttribArray(v1);
		glEnableVertexAttribArray(v2);
		glEnableVertexAttribArray(v3);

		glBindBuffer(GL_ARRAY_BUFFER, scene.getSUVBOHandle());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scene.getSUVBOIndex());

		glVertexAttribPointer(v0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof( float ) * 0));
	    glVertexAttribPointer(v1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof( float ) * 4));
		glVertexAttribPointer(v2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof( float ) * 7));
		glVertexAttribPointer(v3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof( float ) * 9));

		model = glm::translate(model, glm::vec3(-1.3, -2.0, -1.0));
		model = glm::rotate(model, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75, 0.75, 0.75));

		glm::mat4 modelview = view * model;
		glm::mat4 normal = glm::transpose(glm::inverse(modelview));
		glm::mat4 modelview_projection = projection * modelview;

		// pass the matrix to the shader as a uniform
		glUniformMatrix4fv(m0, 1, GL_FALSE, glm::value_ptr(modelview));
		glUniformMatrix4fv(m1, 1, GL_FALSE, glm::value_ptr(normal));
		glUniformMatrix4fv(m2, 1, GL_FALSE, glm::value_ptr(modelview_projection));

		glUniformMatrix4fv(m3, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(m4, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(m5, 1, GL_FALSE, glm::value_ptr(model));

		glUniform3fv(c0, 1, glm::value_ptr(scene.getSU().getAmbientColor()));
		glUniform3fv(c1, 1, glm::value_ptr(scene.getSU().getDiffuseColor()));
		glUniform3fv(c2, 1, glm::value_ptr(scene.getSU().getSpecularColor()));
		glUniform1f(c3, scene.getSU().getShininess());
		glUniform4fv(c4, 1, glm::value_ptr(lightPosition));

		glDrawElements(GL_TRIANGLES, scene.getSU().getNumIndices(), GL_UNSIGNED_INT, (GLvoid*)0);

		model = mv.top();  mv.pop();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// restore default polygon mode

		glDisableClientState(v0);
        glDisableClientState(v1);
		glDisableClientState(v2);
		glDisableClientState(v3);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, NULL);
		glUseProgram(0);
	}

	void Renderer::drawReflectSphere(SceneManager& scene, glm::mat4& view, glm::mat4& model, glm::mat4& projection, glm::vec4& lightPosition, std::stack<glm::mat4>& mv) {
		
		mv.push(model);
		glUseProgram(scene.getReflectShader().getProgramObject());

		if (scene.getWireframe()) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// draw as wireframe
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, scene.getCubeMapTextureHandle());
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE ); // Don't do any blending on the cube map textures

		GLuint uniloc = glGetUniformLocation(scene.getReflectShader().getProgramObject(), "cubemap");
		if (uniloc >= 0) {
			glUniform1i(uniloc, 0);
		}

		GLuint v0 = glGetAttribLocation(scene.getReflectShader().getProgramObject(), "vertexPosition");
		GLuint v1 = glGetAttribLocation(scene.getReflectShader().getProgramObject(), "vertexNormal");
		
		GLuint m0 = glGetUniformLocation(scene.getReflectShader().getProgramObject(), "normalMatrix");
		GLuint m1 = glGetUniformLocation(scene.getReflectShader().getProgramObject(), "MVP");
		GLuint m2 = glGetUniformLocation(scene.getReflectShader().getProgramObject(), "modelMatrix");
		GLuint m3 = glGetUniformLocation(scene.getReflectShader().getProgramObject(), "modelViewMatrix");
		GLuint m4 = glGetUniformLocation(scene.getReflectShader().getProgramObject(), "inverseViewMatrix");

		GLuint c0 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "ambientColor");
		GLuint c1 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "diffuseColor");
		GLuint c2 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "specularColor");
		GLuint c3 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "shininess");
		GLuint c4 = glGetUniformLocation(scene.getBumpShader().getProgramObject(), "lightPosition");
		
		glEnableVertexAttribArray(v0);
		glEnableVertexAttribArray(v1);

		glBindBuffer(GL_ARRAY_BUFFER, scene.getSphereVBOHandle());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scene.getSphereVBOIndex());

		glVertexAttribPointer(v0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof( float ) * 0));
	    glVertexAttribPointer(v1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof( float ) * 4));

		model = glm::translate(model, glm::vec3(3.0, -4.5, -8.0));
		model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));

		glm::mat4 modelview = view * model;
		glm::mat4 normal = glm::transpose(glm::inverse(modelview));
		glm::mat4 modelview_projection = projection * modelview;
		glm::mat4 inverseview = glm::inverse(view);

		// pass the matrix to the shader as a uniform
		glUniformMatrix4fv(m0, 1, GL_FALSE, glm::value_ptr(normal));
		glUniformMatrix4fv(m1, 1, GL_FALSE, glm::value_ptr(modelview_projection));
		glUniformMatrix4fv(m2, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(m3, 1, GL_FALSE, glm::value_ptr(modelview));
		glUniformMatrix4fv(m4, 1, GL_FALSE, glm::value_ptr(inverseview));

		glUniform3fv(c0, 1, glm::value_ptr(scene.getSphere().getAmbientColor()));
		glUniform3fv(c1, 1, glm::value_ptr(scene.getSphere().getDiffuseColor()));
		glUniform3fv(c2, 1, glm::value_ptr(scene.getSphere().getSpecularColor()));
		glUniform1f(c3, scene.getSphere().getShininess());
		glUniform4fv(c4, 1, glm::value_ptr(lightPosition));

		glDrawElements(GL_TRIANGLES, scene.getSphere().getNumIndices(), GL_UNSIGNED_INT, (GLvoid*)0);

		model = mv.top();  mv.pop();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// restore default polygon mode

		glDisableClientState(v0);
        glDisableClientState(v1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, NULL);
		glUseProgram(0);
	}
	
	void Renderer::drawCubeMap(SceneManager& scene, glm::mat4& view, glm::mat4& model, glm::mat4& projection, glm::vec4& lightPosition, std::stack<glm::mat4>& mv) {
		
		mv.push(model);
		model = glm::mat4(1.0f);
		glUseProgram(scene.getCubeMapShader().getProgramObject());
		
		//glEnable(GL_TEXTURE_CUBE_MAP);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, scene.getCubeMapTextureHandle());
		glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE ); // Don't do any blending on the cube map textures

		GLuint uniloc = glGetUniformLocation(scene.getCubeMapShader().getProgramObject(), "cubemap");
		if (uniloc >= 0) {
			glUniform1i(uniloc, 0);
		}
		
		GLuint v0 = glGetAttribLocation(scene.getCubeMapShader().getProgramObject(), "vertexPosition");
		GLuint m0 = glGetUniformLocation(scene.getCubeMapShader().getProgramObject(), "MVP");
		
		glEnableVertexAttribArray(v0);

		glBindBuffer(GL_ARRAY_BUFFER, scene.getCubeMapVBOHandle());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scene.getCubeMapVBOIndex());

		glVertexAttribPointer(v0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof( float ) * 0));

		model = glm::scale(model, glm::vec3(10.0, 10.0, 10.0));

		glm::mat4 modelview = view * model;
		glm::mat4 modelview_projection = projection * modelview;

		// pass the matrix to the shader as a uniform
		glUniformMatrix4fv(m0, 1, GL_FALSE, glm::value_ptr(modelview_projection));

		glDrawElements(GL_QUADS, scene.getCubeMap().getNumIndices(), GL_UNSIGNED_INT, (GLvoid*)0);

		model = mv.top();  mv.pop();

		glDisableClientState(v0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, NULL);
		//glDisable(GL_TEXTURE_CUBE_MAP);
		glUseProgram(0);
	}

	void Renderer::drawSUShadow(SceneManager& scene, glm::mat4& view, glm::mat4& model, glm::mat4& projection, glm::vec4& lightPosition, std::stack<glm::mat4>& mv) {
		glm::vec3 floorV0, floorV1, floorV2;
		getFloorTopPlane(scene, floorV0, floorV1, floorV2);
		glm::vec4 shadowPlane = findPlane(floorV0, floorV1, floorV2);
		glm::mat4 shadowMatrix = getShadowMatrix(shadowPlane, lightPosition);

		// create shadow by rendering cube using shadow matrix
		glStencilFunc(GL_LESS, 2, 0xffffffff);
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		mv.push(model);
		model = glm::mat4(1.0f);

		glUseProgram(scene.getPlainShader().getProgramObject());

		GLuint v0 = glGetAttribLocation(scene.getPlainShader().getProgramObject(), "vertexPosition");
		GLuint c0 = glGetUniformLocation(scene.getPlainShader().getProgramObject(), "vertexColor");
		GLuint m0 = glGetUniformLocation(scene.getPlainShader().getProgramObject(), "MVP");
		
		glEnableVertexAttribArray(v0);

		glBindBuffer(GL_ARRAY_BUFFER, scene.getSUVBOHandle());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scene.getSUVBOIndex());

		glVertexAttribPointer(v0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof( float ) * 0));

		model = glm::translate(model, glm::vec3(-1.3, -2.0, -1.0));
		model = glm::rotate(model, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.75, 0.75, 0.75));

		model = glm::translate(model, glm::vec3(0.0, 0.01, 0.0)); // offset
		model = shadowMatrix * model;

		glm::mat4 modelview = view * model;
		glm::mat4 modelview_projection = projection * modelview;

		glUniformMatrix4fv(m0, 1, GL_FALSE, glm::value_ptr(modelview_projection));

		glm::vec3 shadowColor = glm::vec3(0.1, 0.1, 0.1);
		glUniform3fv(c0, 1, glm::value_ptr(shadowColor));

		glDrawElements(GL_TRIANGLES, scene.getSU().getNumIndices(), GL_UNSIGNED_INT, (GLvoid*)0);

		model = mv.top();  mv.pop();

		glDisable(GL_BLEND);
		glDisableClientState(v0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}

	glm::mat4 Renderer::getShadowMatrix(const glm::vec4& plane, const glm::vec4& lightPosition) {

		glm::mat4 shadow;
		float dot = glm::dot(plane, lightPosition);

		shadow[0][0] = dot - lightPosition[0] * plane[0]; 
		shadow[1][0] = - lightPosition[0] * plane[1]; 
		shadow[2][0] = - lightPosition[0] * plane[2]; 
		shadow[3][0] = - lightPosition[0] * plane[3]; 

		shadow[0][1] = - lightPosition[1] * plane[0]; 
		shadow[1][1] = dot - lightPosition[1] * plane[1]; 
		shadow[2][1] = - lightPosition[1] * plane[2]; 
		shadow[3][1] = - lightPosition[1] * plane[3]; 

		shadow[0][2] = - lightPosition[2] * plane[0]; 
		shadow[1][2] = - lightPosition[2] * plane[1]; 
		shadow[2][2] = dot - lightPosition[2] * plane[2]; 
		shadow[3][2] = - lightPosition[2] * plane[3]; 
	
		shadow[0][3] = - lightPosition[3] * plane[0]; 
		shadow[1][3] = - lightPosition[3] * plane[1]; 
		shadow[2][3] = - lightPosition[3] * plane[2]; 
		shadow[3][3] = dot - lightPosition[3] * plane[3];

		return shadow;
	}

	glm::vec4 Renderer::findPlane(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2) {
		glm::vec4 plane;
		glm::vec3 vec0, vec1;

		vec0 = v1 - v0;
		vec1 = v2 - v0;
		
		// Find cross product to get A, B, C, and D of plane equation
		plane[0] =  vec0[1] * vec1[2] - vec0[2] * vec1[1];
		plane[1] = -(vec0[0] * vec1[2] - vec0[2] * vec1[0]);
		plane[2] =   vec0[0] * vec1[1] - vec0[1] * vec1[0];
		plane[3] = -(plane[0] * v0[0] + plane[1] * v0[1] + plane[2] * v0[2]);

		glm::normalize(plane);

		return plane;
	}

	void Renderer::getFloorTopPlane(SceneManager& scene, glm::vec3& v0, glm::vec3& v1, glm::vec3& v2) {
		
		// get coordinates for points with normal in positive Y direction
		v0[0] = scene.getFloor().getVertexList().at(34).getX();
		v0[1] = scene.getFloor().getVertexList().at(34).getY();
		v0[2] = scene.getFloor().getVertexList().at(34).getZ();

		v1[0] = scene.getFloor().getVertexList().at(35).getX();
		v1[1] = scene.getFloor().getVertexList().at(35).getY();
		v1[2] = scene.getFloor().getVertexList().at(35).getZ();

		v2[0] = scene.getFloor().getVertexList().at(33).getX();
		v2[1] = scene.getFloor().getVertexList().at(33).getY();
		v2[2] = scene.getFloor().getVertexList().at(33).getZ();

		// adjust for the translation which is done in drawFloor()
		v0[1] -= 2.5;
		v1[1] -= 2.5;
		v2[1] -= 2.5;
	}
	
}
