package zombie.util;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.function.Consumer;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import javax.xml.bind.Unmarshaller;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.Attr;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.Text;
import org.xml.sax.SAXException;
import zombie.ZomboidFileSystem;
import zombie.core.logger.ExceptionLogger;
import zombie.util.PZXmlUtil.MarshallerAllocator;
import zombie.util.PZXmlUtil.UnmarshallerAllocator;

public final class PZXmlUtil {
   private static boolean s_debugLogging = false;
   private static final ThreadLocal<DocumentBuilder> documentBuilders = ThreadLocal.withInitial(() -> {
      try {
         DocumentBuilderFactory var0 = DocumentBuilderFactory.newInstance();
         return var0.newDocumentBuilder();
      } catch (ParserConfigurationException var1) {
         ExceptionLogger.logException(var1);
         throw new RuntimeException(var1);
      }
   });

   public static Element parseXml(String var0) throws PZXmlParserException {
      String var1 = ZomboidFileSystem.instance.resolveFileOrGUID(var0);

      Element var2;
      try {
         var2 = parseXmlInternal(var1);
      } catch (IOException | SAXException var6) {
         throw new PZXmlParserException("Exception thrown while parsing XML file \"" + var1 + "\"", var6);
      }

      var2 = includeAnotherFile(var2, var1);
      String var3 = var2.getAttribute("x_extends");
      if (var3 != null && var3.trim().length() != 0) {
         if (!ZomboidFileSystem.instance.isValidFilePathGuid(var3)) {
            var3 = ZomboidFileSystem.instance.resolveRelativePath(var1, var3);
         }

         Element var4 = parseXml(var3);
         return resolve(var2, var4);
      } else {
         return var2;
      }
   }

   private static Element includeAnotherFile(Element var0, String var1) throws PZXmlParserException {
      String var2 = var0.getAttribute("x_include");
      if (var2 != null && var2.trim().length() != 0) {
         if (!ZomboidFileSystem.instance.isValidFilePathGuid(var2)) {
            var2 = ZomboidFileSystem.instance.resolveRelativePath(var1, var2);
         }

         Element var3 = parseXml(var2);
         if (!var3.getTagName().equals(var0.getTagName())) {
            return var0;
         } else {
            Document var4 = createNewDocument();
            Node var5 = var4.importNode(var0, true);
            Node var6 = var5.getFirstChild();

            for (Node var7 = var3.getFirstChild(); var7 != null; var7 = var7.getNextSibling()) {
               if (var7 instanceof Element) {
                  Element var8 = (Element)var4.importNode(var7, true);
                  var5.insertBefore(var8, var6);
               }
            }

            var5.normalize();
            return (Element)var5;
         }
      } else {
         return var0;
      }
   }

   private static Element resolve(Element var0, Element var1) {
      Document var2 = createNewDocument();
      Element var3 = resolve(var0, var1, var2);
      var2.appendChild(var3);
      if (s_debugLogging) {
         System.out
            .println(
               "PZXmlUtil.resolve> \r\n<Parent>\r\n"
                  + elementToPrettyStringSafe(var1)
                  + "\r\n</Parent>\r\n<Child>\r\n"
                  + elementToPrettyStringSafe(var0)
                  + "\r\n</Child>\r\n<Resolved>\r\n"
                  + elementToPrettyStringSafe(var3)
                  + "\r\n</Resolved>"
            );
      }

      return var3;
   }

   private static Element resolve(Element var0, Element var1, Document var2) {
      if (isTextOnly(var0)) {
         return (Element)var2.importNode(var0, true);
      } else {
         Element var3 = var2.createElement(var0.getTagName());
         ArrayList var4 = new ArrayList();
         NamedNodeMap var5 = var1.getAttributes();

         for (int var6 = 0; var6 < var5.getLength(); var6++) {
            Node var7 = var5.item(var6);
            if (!(var7 instanceof Attr)) {
               if (s_debugLogging) {
                  System.out.println("PZXmlUtil.resolve> Skipping parent.attrib: " + var7);
               }
            } else {
               Attr var8 = (Attr)var2.importNode(var7, true);
               var4.add(var8);
            }
         }

         NamedNodeMap var20 = var0.getAttributes();

         for (int var23 = 0; var23 < var20.getLength(); var23++) {
            Node var28 = var20.item(var23);
            if (!(var28 instanceof Attr)) {
               if (s_debugLogging) {
                  System.out.println("PZXmlUtil.resolve> Skipping attrib: " + var28);
               }
            } else {
               Attr var9 = (Attr)var2.importNode(var28, true);
               String var10 = var9.getName();
               boolean var11 = true;

               for (int var12 = 0; var12 < var4.size(); var12++) {
                  Attr var13 = (Attr)var4.get(var12);
                  String var14 = var13.getName();
                  if (var14.equals(var10)) {
                     var4.set(var12, var9);
                     var11 = false;
                     break;
                  }
               }

               if (var11) {
                  var4.add(var9);
               }
            }
         }

         for (Attr var29 : var4) {
            var3.setAttributeNode(var29);
         }

         var4 = new ArrayList();
         HashMap var19 = new HashMap();

         for (Node var21 = var1.getFirstChild(); var21 != null; var21 = var21.getNextSibling()) {
            if (!(var21 instanceof Element)) {
               if (s_debugLogging) {
                  System.out.println("PZXmlUtil.resolve> Skipping parent.node: " + var21);
               }
            } else {
               Element var25 = (Element)var2.importNode(var21, true);
               String var30 = var25.getTagName();
               var19.put(var30, 1 + var19.getOrDefault(var30, 0));
               var4.add(var25);
            }
         }

         HashMap var22 = new HashMap();

         for (Node var26 = var0.getFirstChild(); var26 != null; var26 = var26.getNextSibling()) {
            if (!(var26 instanceof Element)) {
               if (s_debugLogging) {
                  System.out.println("PZXmlUtil.resolve> Skipping node: " + var26);
               }
            } else {
               Element var31 = (Element)var2.importNode(var26, true);
               String var33 = var31.getTagName();
               int var34 = var22.getOrDefault(var33, 0);
               int var35 = 1 + var34;
               var22.put(var33, var35);
               int var36 = var19.getOrDefault(var33, 0);
               if (var36 < var35) {
                  var4.add(var31);
               } else {
                  int var37 = 0;

                  for (int var38 = 0; var37 < var4.size(); var37++) {
                     Element var15 = (Element)var4.get(var37);
                     String var16 = var15.getTagName();
                     if (var16.equals(var33)) {
                        if (var38 == var34) {
                           Element var17 = resolve(var31, var15, var2);
                           var4.set(var37, var17);
                           break;
                        }

                        var38++;
                     }
                  }
               }
            }
         }

         for (Element var32 : var4) {
            var3.appendChild(var32);
         }

         return var3;
      }
   }

   private static boolean isTextOnly(Element var0) {
      boolean var1 = false;

      for (Node var2 = var0.getFirstChild(); var2 != null; var2 = var2.getNextSibling()) {
         boolean var3 = false;
         if (var2 instanceof Text) {
            String var4 = var2.getTextContent();
            boolean var5 = StringUtils.isNullOrWhitespace(var4);
            var3 = !var5;
         }

         if (!var3) {
            var1 = false;
            break;
         }

         var1 = true;
      }

      return var1;
   }

   private static String elementToPrettyStringSafe(Element var0) {
      try {
         return elementToPrettyString(var0);
      } catch (TransformerException var2) {
         return null;
      }
   }

   private static String elementToPrettyString(Element var0) throws TransformerException {
      Transformer var1 = TransformerFactory.newInstance().newTransformer();
      var1.setOutputProperty("indent", "yes");
      var1.setOutputProperty("omit-xml-declaration", "yes");
      var1.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "4");
      StreamResult var2 = new StreamResult(new StringWriter());
      DOMSource var3 = new DOMSource(var0);
      var1.transform(var3, var2);
      return var2.getWriter().toString();
   }

   public static Document createNewDocument() {
      DocumentBuilder var0 = documentBuilders.get();
      return var0.newDocument();
   }

   private static Element parseXmlInternal(String var0) throws SAXException, IOException {
      try {
         Element var6;
         try (
            FileInputStream var1 = new FileInputStream(var0);
            BufferedInputStream var2 = new BufferedInputStream(var1);
         ) {
            DocumentBuilder var3 = documentBuilders.get();
            Document var4 = var3.parse(var2);
            var2.close();
            Element var5 = var4.getDocumentElement();
            var5.normalize();
            var6 = var5;
         }

         return var6;
      } catch (SAXException var11) {
         System.err.println("Exception parsing filename: " + var0);
         throw var11;
      }
   }

   public static void forEachElement(Element var0, Consumer<Element> var1) {
      for (Node var2 = var0.getFirstChild(); var2 != null; var2 = var2.getNextSibling()) {
         if (var2 instanceof Element) {
            var1.accept((Element)var2);
         }
      }
   }

   public static <T> T parse(Class<T> var0, String var1) throws PZXmlParserException {
      Element var2 = parseXml(var1);

      try {
         Unmarshaller var3 = UnmarshallerAllocator.get(var0);
         return (T)var3.unmarshal(var2);
      } catch (JAXBException var5) {
         throw new PZXmlParserException("Exception thrown loading source: \"" + var1 + "\". Loading for type \"" + var0 + "\"", var5);
      }
   }

   public static <T> void write(T var0, File var1) throws TransformerException, IOException, JAXBException {
      Document var2 = createNewDocument();
      Marshaller var3 = MarshallerAllocator.get(var0);
      var3.marshal(var0, var2);
      write(var2, var1);
   }

   public static void write(Document var0, File var1) throws TransformerException, IOException {
      Element var2 = var0.getDocumentElement();
      String var3 = elementToPrettyString(var2);
      FileOutputStream var4 = new FileOutputStream(var1, false);
      PrintWriter var5 = new PrintWriter(var4);
      var5.write(var3);
      var5.flush();
      var4.flush();
      var4.close();
   }

   public static <T> boolean tryWrite(T var0, File var1) {
      try {
         write(var0, var1);
         return true;
      } catch (IOException | JAXBException | TransformerException var3) {
         ExceptionLogger.logException(var3, "Exception thrown writing data: \"" + var0 + "\". Out file: \"" + var1 + "\"");
         return false;
      }
   }

   public static boolean tryWrite(Document var0, File var1) {
      try {
         write(var0, var1);
         return true;
      } catch (IOException | TransformerException var3) {
         ExceptionLogger.logException(var3, "Exception thrown writing document: \"" + var0 + "\". Out file: \"" + var1 + "\"");
         return false;
      }
   }
}
