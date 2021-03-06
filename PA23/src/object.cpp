#include "object.h"

Object::Object() {

}

Object::~Object() {
  vertices.clear();
  indices.clear();
}

bool Object::Init(const std::string& filename) {
  if (!LoadVerticiesFromFile(filename)) {
    printf("Error loading file\n");
    return false;
  }

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
  return true;
}

bool Object::LoadVerticiesFromFile(const std::string& filename) {
  //declare incoming variables stuff
  Assimp::Importer importer;
  const aiScene* aiScene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenNormals);
  if (aiScene == NULL) {
    std::cerr << "File contents had problmes but was successfully opened." << std::endl;
    return false;
  }

    // iterate through the meshes and go through
  for(unsigned int meshIndex = 0; meshIndex < aiScene->mNumMeshes; meshIndex++) {
    int numFacesInMesh = aiScene->mMeshes[meshIndex]->mNumFaces;
    //iterate through faces
    for(int faceIndex = 0; faceIndex < numFacesInMesh; faceIndex++) {
      //helper
      Vertex tempVert(glm::vec3(0.0), glm::vec3(0.0), glm::vec3(0.0), glm::vec2(0.0));

      //get val from faces' mIndeces array
      for(int i = 0; i < 3; i++) {
        //go to aiMesh's mVertices Array
        int vertexIndex = aiScene->mMeshes[meshIndex]->mFaces[faceIndex].mIndices[i];

        //get position
        for (int j = 0; j < 3; j++) {
          tempVert.position[j] = aiScene->mMeshes[meshIndex]->mVertices[vertexIndex][j];
          tempVert.color[j] =  float(rand()%100) / 100.0f;
          tempVert.normal[j] = aiScene->mMeshes[meshIndex]->mNormals[vertexIndex][j];
        }

        for (int j = 0; j < 2; j++) {
          tempVert.texCoord[j] = aiScene->mMeshes[meshIndex]->mNormals[vertexIndex][j];
        }

        //add to the final vec
        vertices.push_back(tempVert);
        indices.push_back(vertexIndex);
      }
    }
  }
  return true;
}

void Object::Update(unsigned int dt) {
  // angle += dt * M_PI/1000;
  // model = glm::rotate(glm::mat4(1.0f), (angle), glm::vec3(0.0, 1.0, 0.0));
}

glm::mat4 Object::GetModel() {
  return model;
}

void Object::Render() {
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,normal));
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,texCoord));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(3);
}
