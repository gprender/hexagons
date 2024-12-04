#include "config.h"

class Material {
public:
	Material(std::string filename);
	~Material();
	void use();

private:
	OpenGlId texture;
};
