#ifndef JAVAX_XML_TRANSFORM_TRANSFORMERFACTORY_H
#define JAVAX_XML_TRANSFORM_TRANSFORMERFACTORY_H

#include "javax/xml/transform/Transformer.h"

namespace javax { namespace xml { namespace transform {

class TransformerFactory {
public:
 static TransformerFactory* newInstance() { static TransformerFactory f; return &f; }
 Transformer* newTransformer() { static Transformer t; return &t; }
};

}}} // namespace javax::xml::transform

#endif // JAVAX_XML_TRANSFORM_TRANSFORMERFACTORY_H
