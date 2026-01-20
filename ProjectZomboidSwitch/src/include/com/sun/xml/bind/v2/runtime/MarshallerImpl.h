#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/marshaller/CharacterEscapeHandler.h"
#include "com/sun/xml/bind/marshaller/DataWriter.h"
#include "com/sun/xml/bind/marshaller/DumbEscapeHandler.h"
#include "com/sun/xml/bind/marshaller/MinimumEscapeHandler.h"
#include "com/sun/xml/bind/marshaller/NamespacePrefixMapper.h"
#include "com/sun/xml/bind/marshaller/NioEscapeHandler.h"
#include "com/sun/xml/bind/marshaller/SAX2DOMEx.h"
#include "com/sun/xml/bind/marshaller/XMLWriter.h"
#include "com/sun/xml/bind/v2/runtime/MarshallerImpl/1.h"
#include "com/sun/xml/bind/v2/runtime/MarshallerImpl/2.h"
#include "com/sun/xml/bind/v2/runtime/output/C14nXmlOutput.h"
#include "com/sun/xml/bind/v2/runtime/output/Encoded.h"
#include "com/sun/xml/bind/v2/runtime/output/ForkXmlOutput.h"
#include "com/sun/xml/bind/v2/runtime/output/IndentingUTF8XmlOutput.h"
#include "com/sun/xml/bind/v2/runtime/output/SAXOutput.h"
#include "com/sun/xml/bind/v2/runtime/output/UTF8XmlOutput.h"
#include "com/sun/xml/bind/v2/runtime/output/XMLEventWriterOutput.h"
#include "com/sun/xml/bind/v2/runtime/output/XMLStreamWriterOutput.h"
#include "com/sun/xml/bind/v2/runtime/output/XmlOutput.h"
#include "com/sun/xml/bind/v2/util/FatalAdapter.h"
#include "java/net/URI.h"
#include "java/net/URISyntaxException.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/MarshalException.h"
#include "javax/xml/bind/Marshaller/Listener.h"
#include "javax/xml/bind/PropertyException.h"
#include "javax/xml/bind/ValidationEvent.h"
#include "javax/xml/bind/ValidationEventHandler.h"
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"
#include "javax/xml/bind/attachment/AttachmentMarshaller.h"
#include "javax/xml/bind/helpers/AbstractMarshallerImpl.h"
#include "javax/xml/namespace/NamespaceContext.h"
#include "javax/xml/stream/XMLEventWriter.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "javax/xml/stream/XMLStreamWriter.h"
#include "javax/xml/transform/Result.h"
#include "javax/xml/transform/dom/DOMResult.h"
#include "javax/xml/transform/sax/SAXResult.h"
#include "javax/xml/transform/stream/StreamResult.h"
#include "javax/xml/validation/Schema.h"
#include "javax/xml/validation/ValidatorHandler.h"
#include "org/w3c/dom/Document.h"
#include "org/w3c/dom/Node.h"
#include "org/xml/sax/SAXException.h"
#include "org/xml/sax/helpers/XMLFilterImpl.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class MarshallerImpl : public AbstractMarshallerImpl {
public:
    static const Logger LOGGER = Logger.getLogger(MarshallerImpl.class.getName());
    std::string indent = "    ";
    NamespacePrefixMapper prefixMapper = nullptr;
    CharacterEscapeHandler escapeHandler = nullptr;
    std::string header = nullptr;
    const JAXBContextImpl context;
    const XMLSerializer serializer;
    Schema schema;
    Listener externalListener = nullptr;
    bool c14nSupport;
    Flushable toBeFlushed;
    Closeable toBeClosed;
    static const std::string INDENT_STRING = "com.sun.xml.bind.indentString";
    static const std::string PREFIX_MAPPER = "com.sun.xml.bind.namespacePrefixMapper";
    static const std::string ENCODING_HANDLER = "com.sun.xml.bind.characterEscapeHandler";
    static const std::string ENCODING_HANDLER2 = "com.sun.xml.bind.marshaller.CharacterEscapeHandler";
    static const std::string XMLDECLARATION = "com.sun.xml.bind.xmlDeclaration";
    static const std::string XML_HEADERS = "com.sun.xml.bind.xmlHeaders";
    static const std::string C14N = "com.sun.xml.bind.c14n";
    static const std::string OBJECT_IDENTITY_CYCLE_DETECTION = "com.sun.xml.bind.objectIdentitityCycleDetection";

    public MarshallerImpl(JAXBContextImpl c, AssociationMap assoc) {
      this.context = c;
      this.serializer = std::make_shared<XMLSerializer>(this);
      this.c14nSupport = this.context.c14nSupport;

      try {
         this.setEventHandler(this);
      } catch (JAXBException var4) {
         throw AssertionError(var4);
      }
   }

    JAXBContextImpl getContext() {
      return this.context;
   }

    void marshal(void* obj, OutputStream out, NamespaceContext inscopeNamespace) {
      this.write(obj, this.createWriter(out), std::make_shared<StAXPostInitAction>(inscopeNamespace, this.serializer));
   }

    void marshal(void* obj, XMLStreamWriter writer) {
      this.write(obj, XMLStreamWriterOutput.create(writer, this.context, this.escapeHandler), std::make_shared<StAXPostInitAction>(writer, this.serializer));
   }

    void marshal(void* obj, XMLEventWriter writer) {
      this.write(obj, std::make_shared<XMLEventWriterOutput>(writer), std::make_shared<StAXPostInitAction>(writer, this.serializer));
   }

    void marshal(void* obj, XmlOutput output) {
      this.write(obj, output, nullptr);
   }

    XmlOutput createXmlOutput(Result result) {
      if (dynamic_cast<SAXResult*>(result) != nullptr) {
         return std::make_shared<SAXOutput>(((SAXResult)result).getHandler());
      } else if (dynamic_cast<DOMResult*>(result) != nullptr) {
    Node node = ((DOMResult)result).getNode();
         if (node == nullptr) {
    Document doc = JAXBContextImpl.createDom(this.getContext().disableSecurityProcessing);
            ((DOMResult)result).setNode(doc);
            return std::make_shared<SAXOutput>(std::make_shared<SAX2DOMEx>(doc));
         } else {
            return std::make_shared<SAXOutput>(std::make_shared<SAX2DOMEx>(node));
         }
      } else {
         if (dynamic_cast<StreamResult*>(result) != nullptr) {
    StreamResult sr = (StreamResult)result;
            if (sr.getWriter() != nullptr) {
               return this.createWriter(sr.getWriter());
            }

            if (sr.getOutputStream() != nullptr) {
               return this.createWriter(sr.getOutputStream());
            }

            if (sr.getSystemId() != nullptr) {
    std::string fileURL = sr.getSystemId();

               try {
                  fileURL = std::make_shared<URI>(fileURL).getPath();
               } catch (URISyntaxException var6) {
               }

               try {
    FileOutputStream fos = std::make_shared<FileOutputStream>(fileURL);

                  assert this.toBeClosed == nullptr;

                  this.toBeClosed = fos;
                  return this.createWriter(fos);
               } catch (IOException var5) {
                  throw MarshalException(var5);
               }
            }
         }

         throw MarshalException(Messages.UNSUPPORTED_RESULT.format(new Object[0]));
      }
   }

    Runnable createPostInitAction(Result result) {
      if (dynamic_cast<DOMResult*>(result) != nullptr) {
    Node node = ((DOMResult)result).getNode();
         return std::make_shared<DomPostInitAction>(node, this.serializer);
      } else {
    return nullptr;
      }
   }

    void marshal(void* target, Result result) {
      this.write(target, this.createXmlOutput(result), this.createPostInitAction(result));
   }

   protected const <T> void write(Name rootTagName, JaxBeanInfo<T> bi, T obj, XmlOutput out, Runnable postInitAction) throws JAXBException {
      try {
         try {
            this.prewrite(out, true, postInitAction);
            this.serializer.startElement(rootTagName, nullptr);
            if (bi.jaxbType == Void.class || bi.jaxbType == void.class) {
               this.serializer.endNamespaceDecls(nullptr);
               this.serializer.endAttributes();
            } else if (obj == nullptr) {
               this.serializer.writeXsiNilTrue();
            } else {
               this.serializer.childAsXsiType(obj, "root", bi, false);
            }

            this.serializer.endElement();
            this.postwrite();
         } catch (SAXException var19) {
            throw MarshalException(var19);
         } catch (IOException var20) {
            throw MarshalException(var20);
         } catch (XMLStreamException var21) {
            throw MarshalException(var21);
         } finally {
            this.serializer.close();
         }
      } finally {
         this.cleanUp();
      }
   }

    void write(void* obj, XmlOutput out, Runnable postInitAction) {
      try {
         if (obj == nullptr) {
            throw IllegalArgumentException(Messages.NOT_MARSHALLABLE.format(new Object[0]));
         }

         if (this.schema != nullptr) {
    ValidatorHandler validator = this.schema.newValidatorHandler();
            validator.setErrorHandler(std::make_shared<FatalAdapter>(this.serializer));
    XMLFilterImpl f = std::make_shared<1>(this);
            f.setContentHandler(validator);
            out = std::make_shared<ForkXmlOutput>(std::make_shared<2>(this, f), out);
         }

         try {
            this.prewrite(out, this.isFragment(), postInitAction);
            this.serializer.childAsRoot(obj);
            this.postwrite();
         } catch (SAXException var18) {
            throw MarshalException(var18);
         } catch (IOException var19) {
            throw MarshalException(var19);
         } catch (XMLStreamException var20) {
            throw MarshalException(var20);
         } finally {
            this.serializer.close();
         }
      } finally {
         this.cleanUp();
      }
   }

    void cleanUp() {
      if (this.toBeFlushed != nullptr) {
         try {
            this.toBeFlushed.flush();
         } catch (IOException var3) {
            LOGGER.log(Level.SEVERE, var3.getMessage(), (Throwable)var3);
         }
      }

      if (this.toBeClosed != nullptr) {
         try {
            this.toBeClosed.close();
         } catch (IOException var2) {
            LOGGER.log(Level.SEVERE, var2.getMessage(), (Throwable)var2);
         }
      }

      this.toBeFlushed = nullptr;
      this.toBeClosed = nullptr;
   }

    void prewrite(XmlOutput out, bool fragment, Runnable postInitAction) {
      this.serializer.startDocument(out, fragment, this.getSchemaLocation(), this.getNoNSSchemaLocation());
      if (postInitAction != nullptr) {
         postInitAction.run();
      }

      if (this.prefixMapper != nullptr) {
         std::string[] decls = this.prefixMapper.getContextualNamespaceDecls();
         if (decls != nullptr) {
            for (int i = 0; i < decls.length; i += 2) {
    std::string prefix = decls[i];
    std::string nsUri = decls[i + 1];
               if (nsUri != nullptr && prefix != nullptr) {
                  this.serializer.addInscopeBinding(nsUri, prefix);
               }
            }
         }
      }

      this.serializer.setPrefixMapper(this.prefixMapper);
   }

    void postwrite() {
      this.serializer.endDocument();
      this.serializer.reconcileID();
   }

    CharacterEscapeHandler getEscapeHandler() {
      return this.escapeHandler;
   }

    CharacterEscapeHandler createEscapeHandler(const std::string& encoding) {
      if (this.escapeHandler != nullptr) {
         return this.escapeHandler;
      } else if (encoding.startsWith("UTF")) {
         return MinimumEscapeHandler.theInstance;
      } else {
         try {
            return std::make_shared<NioEscapeHandler>(this.getJavaEncoding(encoding));
         } catch (Throwable var3) {
            return DumbEscapeHandler.theInstance;
         }
      }
   }

    XmlOutput createWriter(Writer w, const std::string& encoding) {
      if (!(dynamic_cast<BufferedWriter*>(w) != nullptr)) {
         w = std::make_shared<BufferedWriter>(w);
      }

      assert this.toBeFlushed == nullptr;

      this.toBeFlushed = w;
    CharacterEscapeHandler ceh = this.createEscapeHandler(encoding);
    XMLWriter xw;
      if (this.isFormattedOutput()) {
    DataWriter d = std::make_shared<DataWriter>(w, encoding, ceh);
         d.setIndentStep(this.indent);
         xw = d;
      } else {
         xw = std::make_shared<XMLWriter>(w, encoding, ceh);
      }

      xw.setXmlDecl(!this.isFragment());
      xw.setHeader(this.header);
      return std::make_shared<SAXOutput>(xw);
   }

    XmlOutput createWriter(Writer w) {
      return this.createWriter(w, this.getEncoding());
   }

    XmlOutput createWriter(OutputStream os) {
      return this.createWriter(os, this.getEncoding());
   }

    XmlOutput createWriter(OutputStream os, const std::string& encoding) {
      if (encoding == "UTF-8")) {
         Encoded[] table = this.context.getUTF8NameTable();
    CharacterEscapeHandler ceh = this.createEscapeHandler(encoding);
    UTF8XmlOutput out;
         if (this.isFormattedOutput()) {
            out = std::make_shared<IndentingUTF8XmlOutput>(os, this.indent, table, ceh);
         } else if (this.c14nSupport) {
            out = std::make_shared<C14nXmlOutput>(os, table, this.context.c14nSupport, ceh);
         } else {
            out = std::make_shared<UTF8XmlOutput>(os, table, ceh);
         }

         if (this.header != nullptr) {
            out.setHeader(this.header);
         }

    return out;
      } else {
         try {
            return this.createWriter(std::make_shared<OutputStreamWriter>(os, this.getJavaEncoding(encoding)), encoding);
         } catch (UnsupportedEncodingException var6) {
            throw MarshalException(Messages.UNSUPPORTED_ENCODING.format(new Object[]{encoding}), var6);
         }
      }
   }

    void* getProperty(const std::string& name) {
      if ("com.sun.xml.bind.indentString" == name)) {
         return this.indent;
      } else if ("com.sun.xml.bind.characterEscapeHandler" == name) || "com.sun.xml.bind.marshaller.CharacterEscapeHandler" == name)) {
         return this.escapeHandler;
      } else if ("com.sun.xml.bind.namespacePrefixMapper" == name)) {
         return this.prefixMapper;
      } else if ("com.sun.xml.bind.xmlDeclaration" == name)) {
         return !this.isFragment();
      } else if ("com.sun.xml.bind.xmlHeaders" == name)) {
         return this.header;
      } else if ("com.sun.xml.bind.c14n" == name)) {
         return this.c14nSupport;
      } else {
         return "com.sun.xml.bind.objectIdentitityCycleDetection" == name) ? this.serializer.getObjectIdentityCycleDetection() : super.getProperty(name);
      }
   }

    void setProperty(const std::string& name, void* value) {
      if ("com.sun.xml.bind.indentString" == name)) {
         this.checkString(name, value);
         this.indent = (std::string)value;
      } else if (!"com.sun.xml.bind.characterEscapeHandler" == name) && !"com.sun.xml.bind.marshaller.CharacterEscapeHandler" == name)) {
         if ("com.sun.xml.bind.namespacePrefixMapper" == name)) {
            if (!(dynamic_cast<NamespacePrefixMapper*>(value) != nullptr)) {
               throw PropertyException(Messages.MUST_BE_X.format(new Object[]{name, NamespacePrefixMapper.class.getName(), value.getClass().getName()}));
            } else {
               this.prefixMapper = (NamespacePrefixMapper)value;
            }
         } else if ("com.sun.xml.bind.xmlDeclaration" == name)) {
            this.checkBoolean(name, value);
            super.setProperty("jaxb.fragment", !(bool)value);
         } else if ("com.sun.xml.bind.xmlHeaders" == name)) {
            this.checkString(name, value);
            this.header = (std::string)value;
         } else if ("com.sun.xml.bind.c14n" == name)) {
            this.checkBoolean(name, value);
            this.c14nSupport = (bool)value;
         } else if ("com.sun.xml.bind.objectIdentitityCycleDetection" == name)) {
            this.checkBoolean(name, value);
            this.serializer.setObjectIdentityCycleDetection((bool)value);
         } else {
            super.setProperty(name, value);
         }
      } else if (!(dynamic_cast<CharacterEscapeHandler*>(value) != nullptr)) {
         throw PropertyException(Messages.MUST_BE_X.format(new Object[]{name, CharacterEscapeHandler.class.getName(), value.getClass().getName()}));
      } else {
         this.escapeHandler = (CharacterEscapeHandler)value;
      }
   }

    void checkBoolean(const std::string& name, void* value) {
      if (!(dynamic_cast<bool*>(value) != nullptr)) {
         throw PropertyException(Messages.MUST_BE_X.format(new Object[]{name, bool.class.getName(), value.getClass().getName()}));
      }
   }

    void checkString(const std::string& name, void* value) {
      if (!(dynamic_cast<std*>(value) != nullptr::string)) {
         throw PropertyException(Messages.MUST_BE_X.format(new Object[]{name, std::string.class.getName(), value.getClass().getName()}));
      }
   }

   public <A : public XmlAdapter> void setAdapter(Class<A> type, A adapter) {
      if (type == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         this.serializer.putAdapter(type, adapter);
      }
   }

   public <A : public XmlAdapter> A getAdapter(Class<A> type) {
      if (type == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
         return (A)(this.serializer.containsAdapter(type) ? this.serializer.getAdapter(type) : nullptr);
      }
   }

    void setAttachmentMarshaller(AttachmentMarshaller am) {
      this.serializer.attachmentMarshaller = am;
   }

    AttachmentMarshaller getAttachmentMarshaller() {
      return this.serializer.attachmentMarshaller;
   }

    Schema getSchema() {
      return this.schema;
   }

    void setSchema(Schema s) {
      this.schema = s;
   }

    bool handleEvent(ValidationEvent event) {
    return false;
   }

    Listener getListener() {
      return this.externalListener;
   }

    void setListener(Listener listener) {
      this.externalListener = listener;
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
