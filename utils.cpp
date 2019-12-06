#include "utils.h"

glm::vec4 RGBColor(unsigned int R, unsigned int G, unsigned int B) {
return glm::vec4((float)R/255, (float)G/255, (float)B/255, 1.0);
}