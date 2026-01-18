#!/usr/bin/env python3
"""
Project Zomboid Rosetta Metadata Extractor
Extracts class hierarchy, fields, methods, and documentation from pz-rosetta-source
Optimized with progress tracking and efficient parsing.
"""

import os
import sys
import yaml
import json
from pathlib import Path
from typing import Dict, List, Set, Optional, Any
from collections import defaultdict

try:
    from tqdm import tqdm
except ImportError:
    # Fallback if tqdm not available
    def tqdm(iterable, **kwargs):
        return iterable

class RosettaMetadataExtractor:
    def __init__(self, rosetta_base: str = None):
        self.rosetta_base = rosetta_base or "/workspaces/PZ/pz-rosetta-source-main/rosetta/java"
        self.classes = {}
        self.inheritance_map = defaultdict(list)
        self.interface_implementations = defaultdict(set)
        self.type_hierarchy = {}
        self.callbacks = {}
        self.events = {}
        self.hooks = {}
    
    def load_all_metadata(self):
        """Load all metadata from rosetta source."""
        self._load_java_classes()
        self._load_callbacks()
        self._load_events()
        self._load_hooks()
    
    def _load_java_classes(self):
        """Load Java class documentation."""
        yml_files = list(Path(self.rosetta_base).rglob("*.yml"))
        print(f"Loading {len(yml_files)} Java class documentation files...")
        
        for yml_file in tqdm(yml_files, desc="Loading classes", unit=" files"):
            try:
                with open(yml_file, 'r', encoding='utf-8') as f:
                    data = yaml.safe_load(f)
                    if data and 'languages' in data and 'java' in data['languages']:
                        self._extract_java_classes(data['languages']['java'], str(yml_file))
            except Exception:
                pass
    
    def _extract_java_classes(self, java_data: Dict, source_file: str):
        """Extract class information from Java documentation."""
        if 'packages' not in java_data:
            return
        
        for package_name, classes_dict in java_data['packages'].items():
            for class_name, class_info in classes_dict.items():
                full_name = f"{package_name}.{class_name}"
                
                class_doc = {
                    'package': package_name,
                    'name': class_name,
                    'source': source_file,
                    'modifiers': class_info.get('modifiers', []),
                    'extends': class_info.get('extends', ''),
                    'implements': class_info.get('implements', []),
                    'fields': self._extract_fields(class_info),
                    'methods': self._extract_methods(class_info),
                    'constructors': self._extract_constructors(class_info),
                    'inner_classes': list(class_info.get('inner_classes', {}).keys()) if 'inner_classes' in class_info else [],
                }
                
                self.classes[full_name] = class_doc
                
                # Build inheritance map
                if class_info.get('extends'):
                    parent = class_info['extends']
                    self.inheritance_map[parent].append(full_name)
                
                # Build interface map
                for interface in class_info.get('implements', []):
                    self.interface_implementations[interface].add(full_name)
    
    def _extract_fields(self, class_info: Dict) -> List[Dict]:
        """Extract field information."""
        fields = []
        for field_name, field_info in class_info.get('fields', {}).items():
            fields.append({
                'name': field_name,
                'type': self._type_to_string(field_info.get('type', {})),
                'modifiers': field_info.get('modifiers', []),
                'notes': field_info.get('notes', ''),
            })
        return fields
    
    def _extract_methods(self, class_info: Dict) -> List[Dict]:
        """Extract method information."""
        methods = []
        for method_info in class_info.get('methods', []):
            methods.append({
                'name': method_info.get('name', ''),
                'return_type': self._type_to_string(method_info.get('return_type', {})),
                'parameters': self._extract_parameters(method_info.get('parameters', [])),
                'modifiers': method_info.get('modifiers', []),
                'notes': method_info.get('notes', ''),
                'throws': method_info.get('throws', []),
            })
        return methods
    
    def _extract_constructors(self, class_info: Dict) -> List[Dict]:
        """Extract constructor information."""
        constructors = []
        for ctor_info in class_info.get('constructors', []):
            constructors.append({
                'parameters': self._extract_parameters(ctor_info.get('parameters', [])),
                'modifiers': ctor_info.get('modifiers', []),
                'notes': ctor_info.get('notes', ''),
                'throws': ctor_info.get('throws', []),
            })
        return constructors
    
    def _extract_parameters(self, params: List) -> List[Dict]:
        """Extract parameter information."""
        result = []
        for param in params:
            result.append({
                'name': param.get('name', ''),
                'type': self._type_to_string(param.get('type', {})),
                'notes': param.get('notes', ''),
            })
        return result
    
    def _type_to_string(self, type_info: Any) -> str:
        """Convert type info to string representation."""
        if isinstance(type_info, str):
            return type_info
        if isinstance(type_info, dict):
            basic = type_info.get('basic', '')
            full = type_info.get('full', '')
            if full:
                return full
            return basic
        return str(type_info)
    
    def _load_callbacks(self):
        """Load callback definitions."""
        callbacks_file = os.path.join(os.path.dirname(self.rosetta_base), 'callbacks.yml')
        if os.path.exists(callbacks_file):
            try:
                with open(callbacks_file, 'r') as f:
                    data = yaml.safe_load(f)
                    if data and 'games' in data:
                        pz_data = data['games'].get('projectzomboid', {})
                        self.callbacks = pz_data.get('callbacks', {})
                print(f"Loaded {len(self.callbacks)} callbacks")
            except Exception as e:
                print(f"Error loading callbacks: {e}")
    
    def _load_events(self):
        """Load event definitions."""
        events_file = os.path.join(os.path.dirname(self.rosetta_base), 'events.yml')
        if os.path.exists(events_file):
            try:
                with open(events_file, 'r') as f:
                    data = yaml.safe_load(f)
                    if data and 'games' in data:
                        pz_data = data['games'].get('projectzomboid', {})
                        self.events = pz_data.get('events', {})
                print(f"Loaded {len(self.events)} events")
            except Exception as e:
                print(f"Error loading events: {e}")
    
    def _load_hooks(self):
        """Load hook definitions."""
        hooks_file = os.path.join(os.path.dirname(self.rosetta_base), 'hooks.yml')
        if os.path.exists(hooks_file):
            try:
                with open(hooks_file, 'r') as f:
                    data = yaml.safe_load(f)
                    if data and 'games' in data:
                        pz_data = data['games'].get('projectzomboid', {})
                        self.hooks = pz_data.get('hooks', {})
                print(f"Loaded {len(self.hooks)} hooks")
            except Exception as e:
                print(f"Error loading hooks: {e}")
    
    def get_class_doc(self, class_name: str) -> Optional[Dict]:
        """Get documentation for a class."""
        return self.classes.get(class_name)
    
    def get_class_hierarchy(self, class_name: str) -> List[str]:
        """Get inheritance hierarchy for a class."""
        hierarchy = [class_name]
        current = class_name
        while current in self.classes and self.classes[current].get('extends'):
            parent = self.classes[current]['extends']
            hierarchy.append(parent)
            current = parent
        return hierarchy
    
    def get_implementations(self, interface_name: str) -> Set[str]:
        """Get all classes implementing an interface."""
        return self.interface_implementations.get(interface_name, set())
    
    def export_class_map_json(self, output_file: str):
        """Export class map as JSON for use by conversion tools."""
        class_map = {
            'classes': {},
            'inheritance': dict(self.inheritance_map),
            'interfaces': dict(self.interface_implementations),
            'callbacks': self.callbacks,
            'events': self.events,
            'hooks': self.hooks,
        }
        
        for full_name, doc in self.classes.items():
            class_map['classes'][full_name] = {
                'package': doc['package'],
                'name': doc['name'],
                'modifiers': doc['modifiers'],
                'extends': doc['extends'],
                'implements': doc['implements'],
                'field_count': len(doc['fields']),
                'method_count': len(doc['methods']),
                'constructor_count': len(doc['constructors']),
            }
        
        with open(output_file, 'w') as f:
            json.dump(class_map, f, indent=2)
        
        print(f"Exported class map to {output_file}")
    
    def print_summary(self):
        """Print metadata summary."""
        print("\n" + "="*60)
        print("Rosetta Metadata Summary")
        print("="*60)
        print(f"Classes loaded: {len(self.classes)}")
        print(f"Callbacks: {len(self.callbacks)}")
        print(f"Events: {len(self.events)}")
        print(f"Hooks: {len(self.hooks)}")
        print(f"Interface implementations: {sum(len(v) for v in self.interface_implementations.values())}")
        print("="*60 + "\n")


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 rosetta_extractor.py <output_json> [rosetta_path]")
        sys.exit(1)
    
    rosetta_path = sys.argv[2] if len(sys.argv) > 2 else None
    extractor = RosettaMetadataExtractor(rosetta_path)
    
    print("Loading all metadata...")
    extractor.load_all_metadata()
    extractor.print_summary()
    
    output_file = sys.argv[1]
    extractor.export_class_map_json(output_file)
    print(f"Class map exported to {output_file}")


if __name__ == '__main__':
    main()
