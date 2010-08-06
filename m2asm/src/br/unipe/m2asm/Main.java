package br.unipe.m2asm;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

import br.unipe.m2asm.codegen.IncludeResolver;
import br.unipe.m2asm.codegen.LabelResolver;
import br.unipe.m2asm.codegen.M2CodeGenerator;
import br.unipe.m2asm.codegen.MacroResolver;
import br.unipe.m2asm.codegen.SymbolTable;
import br.unipe.m2asm.parse.ASTProg;
import br.unipe.m2asm.parse.M2AsmParser;
import br.unipe.m2asm.parse.ParseException;
import br.unipe.m2asm.semant.SemanticAnalyzer;
import br.unipe.m2asm.util.Util;

/**
 * 
 * @author Odilon
 *
 */
public class Main {
	private static final String
		SRC_EXT = "m2a",
		INC_EXT = "m2i",
		OBJ_EXT = "bin",
		LST_EXT = "lst";
	
	public static void main(String args[]) {
		if (args.length == 0) {
			System.out.println("Por favor, especifique um nome de arquivo.");
			return;
		}
		String fileName = args[0];
		try {
			ASTProg raiz = parse(fileName);
			System.out.println("[ Árvore de Sintaxe Abstrata ]");
			raiz.dump("");
			
			SymbolTable symTab = new SymbolTable();
			
			IncludeResolver resolver0 = new IncludeResolver();
			resolver0.visit(raiz, symTab);
			System.out.println("\n[ Árvore de Sintaxe Abstrata, após resolver os %INCLUDES ]");
			raiz.dump("");
			
			MacroResolver resolver1 = new MacroResolver();
			resolver1.visit(raiz, symTab);
			System.out.println("\n[ Árvore de Sintaxe Abstrata, após resolver as macros ]");
			raiz.dump("");
			
			//assembly, 1st pass (resolve label addresses, populating symTab)
			LabelResolver resolver2 = new LabelResolver();
			resolver2.visit(raiz, symTab);
			
			//some basic semantic checks
			SemanticAnalyzer semant = new SemanticAnalyzer();
			semant.analyse(raiz, symTab);
						
			//assembly, 2nd pass (code generation proper)
			M2CodeGenerator codeGen = new M2CodeGenerator(resolver2.getCodeSize(), resolver2.getDataSize());
			codeGen.visit(raiz, symTab);
			codeGen.createFile(Util.replaceFileExt(args[0], SRC_EXT, OBJ_EXT));
		} catch (Exception e) {
			System.out.println("Ocorreu um erro:");
			e.printStackTrace();
		}
	}
	
	/**
	 * Isolated from main code, for reuse by %INCLUDE
	 * 
	 * @param fileName
	 * @return
	 * @throws IOException
	 * @throws ParseException
	 */
	public static ASTProg parse(String fileName) throws IOException, ParseException {
		InputStream in = new FileInputStream(fileName);
		M2AsmParser parser = new M2AsmParser(in);
		try {
			System.out.println("Input file: " + fileName);
			ASTProg root = parser.Prog();
			return root;
		} finally {
			in.close();
		}
	}
}
