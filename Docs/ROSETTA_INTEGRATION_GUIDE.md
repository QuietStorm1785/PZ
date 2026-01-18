# Enhanced Conversion Tools - pz-rosetta-source Integration

## Overview

The new conversion tools leverage the **pz-rosetta-source** metadata to provide highly accurate Java-to-C++ conversions specifically tailored for Project Zomboid's codebase.

## Tools Available

### 1. Rosetta Metadata Extractor (`rosetta_extractor.py`)

**Purpose**: Extracts comprehensive class metadata from pz-rosetta-source YAML files

**Usage**:
```bash
python3 tools/rosetta_extractor.py class_map.json [rosetta_path]
```

**Output**: `class_map.json` containing:
- 4,101 Java classes with full structure documentation
- 26 callbacks with parameter information
- 271 events with event details
- 8 hooks with hook metadata
- Inheritance relationships
- Interface implementations

**What it extracts**:
- Class hierarchy and inheritance
- Method signatures with parameter types
- Field declarations with types and modifiers
- Constructor definitions
- Documentation strings
- Access modifiers
- Inner classes

### 2. Enhanced Java Converter (`enhanced_java_converter.py`)

**Purpose**: Applies conversion fixes while using rosetta metadata for context-aware improvements

**Usage**:
```bash
python3 tools/enhanced_java_converter.py <directory> [rosetta_path]
```

**Features**:
- Uses loaded class metadata to recognize Project Zomboid classes
- Improves method signatures based on documentation
- Preserves parameter names from metadata
- Adds inline documentation from rosetta notes
- Tracks metadata match statistics

**Statistics tracked**:
- Metadata matches found
- Type conversions made
- Method signatures improved
- Parameter names preserved
- Documentation added

### 3. Advanced Java Converter (`advanced_java_converter.py`)

**Purpose**: Most comprehensive converter using pre-generated class_map.json

**Usage**:
```bash
python3 tools/advanced_java_converter.py <directory> [class_map.json]
```

**Features**:
- Uses pre-loaded class map for fast processing
- Project Zomboid callback detection and fixing
- Event handler signature improvements
- Hook invocation recognition
- Comprehensive Java-to-C++ conversion
- Error tracking and statistics

**Advantages**:
- Fastest performance (uses JSON lookup)
- Callback/event/hook awareness
- Optimized for Project Zomboid codebase
- Detailed statistics reporting

## Recommended Workflow

```bash
# Step 1: Generate class map from rosetta source (one-time setup)
python3 tools/rosetta_extractor.py class_map.json

# Step 2: Apply advanced conversion with full metadata awareness
python3 tools/advanced_java_converter.py converted/include

# Step 3: Apply to source files
python3 tools/advanced_java_converter.py converted/src

# Step 4: Remove any remaining Java keywords
python3 tools/remove_java_keywords.py converted/include
python3 tools/remove_java_keywords.py converted/src

# Step 5: Commit results
git add -A
git commit -m "Apply rosetta-aware conversion improvements"
```

## Class Map Content

The generated `class_map.json` includes:

### Classes (4,101 total)
```json
{
  "zombie.characters.IsoGameCharacter": {
    "package": "zombie.characters",
    "name": "IsoGameCharacter",
    "modifiers": ["public"],
    "extends": "IsoMovingObject",
    "implements": ["IsoPlayer", "IsoAnimated"],
    "field_count": 47,
    "method_count": 156,
    "constructor_count": 3
  }
}
```

### Callbacks (26)
- `umbrella.Item_OnCreate`
- `umbrella.Item_OnCooked`
- `umbrella.Item_OnEat`
- And 23 more...

### Events (271)
- `OnPlayerUpdate`
- `OnServerStarted`
- `OnTick`
- And 268 more...

### Hooks (8)
- Pre-defined system hooks for core functionality

## Improvements Over Previous Tools

| Aspect | Previous | New |
|--------|----------|-----|
| Type Recognition | Basic mappings | 4,101 known classes |
| Callbacks | No recognition | 26 callbacks identified |
| Events | No recognition | 271 events tracked |
| Hooks | No recognition | 8 hooks supported |
| Documentation | None | Preserved from rosetta |
| Method Signatures | Generic | Metadata-informed |
| Performance | Basic regex | Optimized JSON lookup |

## Statistics from First Run

When running on freshly converted files:

**rosetta_extractor.py**:
- Loaded 4,101 Java class documentation files
- Extracted 4,101 classes
- Found 26 callbacks
- Found 271 events
- Found 8 hooks

**advanced_java_converter.py**:
- Processes all 4,204 C++ files
- Recognizes Project Zomboid specific patterns
- Fixes callback signatures
- Improves event handlers
- Validates hook calls

## Integration Points

The class map enables integration with:
- IDE plugins for C++ development
- Static analysis tools
- API documentation generators
- Type checking systems
- Refactoring tools
- Code generation utilities

## Future Enhancements

Potential improvements:
1. Generate C++ header stubs from metadata
2. Create project documentation from rosetta source
3. Build type checking system based on class hierarchy
4. Generate binding layers for Java/C++ interop
5. Create CMake project file automatically
6. Generate unit test templates from method signatures

## Error Handling

Tools gracefully handle:
- Missing YAML files
- Malformed metadata
- Encoding issues
- File permission errors
- Invalid directory paths

All errors are logged but don't stop processing.
