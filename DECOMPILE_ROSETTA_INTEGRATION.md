# Vineflower + Rosetta Integration

## Overview

The enhanced `decompile_vineflower.py` script now integrates Rosetta documentation from `pz-rosetta-source-main` to enhance decompiled Java source code with:

- **Class Documentation**: Javadoc-style comments added to class declarations
- **Method Documentation**: Parameter descriptions and return value documentation
- **Field Documentation**: Field-level documentation and notes
- **Metadata**: Full class hierarchy and interface implementation tracking

## Features

### 1. Rosetta Documentation Loading
- Loads all `.yml` documentation files from `pz-rosetta-source-main/rosetta/java`
- Extracts class-level, method-level, and field-level documentation
- Tracks inheritance relationships and interface implementations
- Progress tracking with tqdm

### 2. Automatic Enhancement
- Decompiled Java files are automatically enhanced with documentation
- Documentation is inserted as JavaDoc-style comments
- Safe parsing prevents malformation of decompiled code
- Graceful fallback if documentation is unavailable

### 3. Configuration Options
- `--skip-rosetta`: Skip Rosetta enhancement (faster decompilation)
- Rosetta base path is configurable
- Automatic Java home detection (Java 21)

## Usage

### Basic Decompilation with Rosetta Enhancement
```bash
python3 decompile_vineflower.py /workspaces/PZ/classes_only /workspaces/PZ/converted
```

### Skip Rosetta Enhancement (for speed)
```bash
python3 decompile_vineflower.py /workspaces/PZ/classes_only /workspaces/PZ/converted --skip-rosetta
```

### Custom Rosetta Path
Modify the `rosetta_base` parameter in the `RosettaDocumentation` class:
```python
rosetta_docs = RosettaDocumentation("/path/to/custom/rosetta/java")
```

## Implementation Details

### RosettaDocumentation Class
- **`load()`**: Load all YAML documentation files
- **`get_class_doc()`**: Retrieve class documentation
- **`get_method_doc()`**: Retrieve method and parameter documentation
- **`get_field_doc()`**: Retrieve field documentation
- **`_extract_docs()`**: Parse YAML data structure
- **`_extract_params_doc()`**: Extract parameter descriptions

### Enhancement Process
1. Vineflower decompiles `.class` file to Java source
2. RosettaDocumentation matches the class name to documentation
3. JavaDoc comments are inserted before class declaration
4. Enhanced file is written back to output location

## Rosetta Data Structure

The Rosetta format provides:

```yaml
languages:
  java:
    packages:
      package.name:
        ClassName:
          notes: "Class documentation"
          modifiers: ["public", "class"]
          extends: "ParentClass"
          implements: ["Interface1", "Interface2"]
          fields:
            fieldName:
              notes: "Field documentation"
              type: {...}
          methods:
            - name: "methodName"
              notes: "Method documentation"
              return_notes: "Return value description"
              parameters:
                - name: "paramName"
                  notes: "Parameter description"
              return_type: {...}
          constructors: [...]
```

## Output

The script generates:
- Full Java source tree in `/workspaces/PZ/converted`
- Package structure preserved
- Enhanced with Rosetta documentation where available
- Progress tracking and summary statistics

### Example Output
```
============================================================
Decompilation Complete
============================================================
Total files: 3250
Successful: 3242
Failed: 8
Success rate: 99.8%
Output directory: /workspaces/PZ/converted
Enhanced with Rosetta documentation for 2845 classes
============================================================
```

## Performance

- **Parallel decompilation**: 4 worker threads
- **Rosetta loading**: ~2-5 seconds for 2800+ classes
- **Enhancement overhead**: Minimal (happens during decompilation)
- **Total time**: ~15-30 minutes for full codebase (depends on system)

## Troubleshooting

### PyYAML Not Found
```bash
pip install pyyaml
```

### Rosetta Path Not Found
- Verify `/workspaces/PZ/pz-rosetta-source-main/rosetta/java` exists
- Update path in `RosettaDocumentation.__init__()`

### Enhancement Not Applied
- Use `--skip-rosetta` to verify decompilation works
- Check Python version (requires 3.6+)
- Enable verbose output by modifying print statements

## Integration with Existing Tools

### Combining with Java Converter
After decompilation and enhancement:
```bash
python3 /workspaces/PZ/tools/comprehensive_java_converter_v3.py /workspaces/PZ/converted
```

### Using Enhanced Documentation
The Rosetta documentation can be:
- Parsed for API analysis
- Used to generate updated JavaDocs
- Imported into IDE for IntelliSense
- Analyzed for code metrics

## Future Enhancements

Potential improvements:
1. **Callback/Event Injection**: Auto-insert callback and event definitions
2. **Type Annotation**: Enhanced type information from Rosetta
3. **Deprecation Warnings**: Mark deprecated APIs
4. **Version Tracking**: Include version information from Rosetta
5. **Custom Template**: User-defined documentation templates
