package br.unipe.m2asm.codegen;

import java.util.Collection;
import java.util.LinkedHashMap;
import java.util.Map;

import br.unipe.m2asm.util.Util;

/**
 * Maintains information about all declared labels
 *
 * @author Odilon
 *
 */
public class SymbolTable {
	private Map<String, Entry> tab = new LinkedHashMap<String, Entry>();
	
	public void addLabel(String name, int address, Section section) {
		Entry e = new Entry();
		e.name = name;
		e.address = address;
		e.section = section;
		if (tab.containsKey(name)) {
			Util.error("Duplicate label definition: %s", name);
		}
		tab.put(name, e);
	}
	
	/**
	 * Adds just the name, for the case of forward references; i.e. :
	 * when the address is not yet known.
	 * 
	 * @param name
	 */
	public void addLabel(String name, Section section) {
		Entry e = new Entry();
		e.name = name;
		e.section = section;
		if (tab.containsKey(name)) {
			Util.error("Duplicate label definition: %s", name);
		}
		tab.put(name, e);
	}
	
	public void addDef(String name, String value) {
		Entry e = new Entry();
		e.name = name;
		e.value = value;
		if (tab.containsKey(name)) {
			Util.error("Duplicate constant definition: %s", name);
		}
		tab.put(name, e);
	}
	
	/**
	 * Get all registered label ids.
	 * 
	 * @return
	 */
	public Collection<String> getAllLabels() {
		return tab.keySet();
	}
	
	public boolean isEmpty() {
		return tab.isEmpty();
	}
	
	/**
	 * "Patches" a label; i.e. : puts the address to a previously seen label,
	 * when it becomes available.
	 * @param name
	 * @param address
	 */
	public void patchLabel(String name, int address) {
		Entry e = tab.get(name);
		if (e == null) {
			Util.error("Undeclared label: %s", name);
		}
		e.address = address;
		//is this needed?
		tab.put(name, e);
	}
	
	public boolean isLabel(String name) {
		Entry e = tab.get(name);
		if (e == null) {
			return false;
		}
		return e.isLabel();
	}
	
	public boolean isDef(String name) {
		Entry e = tab.get(name);
		if (e == null) {
			return false;
		}
		return e.isDef();
	}
	
	/**
	 * Retrieves the address of a label, relative to the segment it is declared in.
	 * @param name
	 * @return
	 */
	public int resolveLabel(String name) {
		Entry e = tab.get(name);
		if (e == null) {
			Util.error("Undeclared label: %s", name);
		}
		return e.address;
	}
	
	public String resolveDef(String name) {
		Entry e = tab.get(name);
		if (e == null) {
			Util.error("Undeclared constant: %s", name);
		}
		return e.value;
	}
	
	/**
	 * Returns the segment the label is declared in.
	 * @param name
	 * @return
	 */
	public Section getDeclaredSection(String name) {
		Entry e = tab.get(name);
		if (e == null) {
			Util.error("Undeclared label: %s", name);
		}
		return e.section;
	}

	@Override
	public String toString() {
		return tab.values().toString();
	}
	
	public class Entry {
		public String name;
		public Integer address;  //used in case of being a label
		public Section section;  //ditto
		public String value;     //used in case of being a "%DEF" macro
		
		public boolean isLabel() {
			return address != null;
		}
		
		public boolean isDef() {
			return value != null;
		}
		
		@Override
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + getOuterType().hashCode();
			result = prime * result + ((name == null) ? 0 : name.hashCode());
			return result;
		}
		@Override
		public boolean equals(Object obj) {
			if (this == obj)
				return true;
			if (obj == null)
				return false;
			if (!(obj instanceof Entry))
				return false;
			Entry other = (Entry) obj;
			if (!getOuterType().equals(other.getOuterType()))
				return false;
			if (name == null) {
				if (other.name != null)
					return false;
			} else if (!name.equals(other.name))
				return false;
			return true;
		}
		private SymbolTable getOuterType() {
			return SymbolTable.this;
		}
		@Override
		public String toString() {
			if (isLabel()) {
				return Util.format("label: [%s @ 0x%08X : %s]", name, address, section);
			}
			else if (isDef()) {
				return Util.format("def: [%s : %s]", name, value);
			}
			else {
				return Util.format("unknown: [%s]", name);
			}
			///return "[" + name + " @ " + address + " : " + section + "]";
		}
	} //Entry.
}
