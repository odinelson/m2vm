package br.unipe.m2asm.codegen;

import br.unipe.m2asm.machine.Machine;
import br.unipe.m2asm.parse.ASTChar;
import br.unipe.m2asm.parse.ASTDeclarator;
import br.unipe.m2asm.parse.ASTInteger;
import br.unipe.m2asm.parse.ASTLabel;
import br.unipe.m2asm.parse.ASTPseudoStmt;
import br.unipe.m2asm.parse.ASTSegment;
import br.unipe.m2asm.parse.ASTStmt;
import br.unipe.m2asm.parse.ASTStr;
import br.unipe.m2asm.parse.ASTValues;
import br.unipe.m2asm.parse.M2AsmNode;
import br.unipe.m2asm.parse.M2AsmParserVisitorAdapter;

/**
 * Responsável por encontrar os endereços de todos os labels.
 * Também pré-calcula os tamanhos dos segmentos de código e dados, para melhor desempenho do gerador de código
 * (assim, o gerador não precisa descobrir esses tamanhos iterando as listas de arrays de bytes gerados...)
 * Deve executar antes do gerador de código propriamente dito.
 * 
 * @author Odilon
 *
 */
public class LabelResolver extends M2AsmParserVisitorAdapter {

	private Section currSection;
	private int currCodeAddress = 0;
	private int currDataAddress = 0;
	private String lastGlobalLabel;
	
	public int getCodeSize() {
		return currCodeAddress;
	}
	
	public int getDataSize() {
		return currDataAddress;
	}
	
	@Override
	public void visit(ASTSegment node, SymbolTable data) {
		currSection = Section.valueOf(node.value);
		super.visit(node, data);
	}

	@Override
	public void visit(ASTLabel node, SymbolTable data) {
		super.visit(node, data);
		if (!node.value.startsWith(".")) {
			lastGlobalLabel = node.value;
		}
		int address = currSection == Section.CODE ? currCodeAddress : currDataAddress;
		data.addLabel(node.value, address, currSection);
		if (node.value.startsWith(".")) {  //local label (TODO : use this logic everyhere... here i'm adding 2 labels at once...)
			data.addLabel(lastGlobalLabel+node.value, address, currSection);
		}
	}

	@Override
	public void visit(ASTStmt node, SymbolTable data) {
		super.visit(node, data);
		currCodeAddress += Machine.WORD_SIZE;
	}

	@Override
	public void visit(ASTPseudoStmt node, SymbolTable data) {
		super.visit(node, data);
		//here the stuff is more complicated; here, we must detect the size of
		//the data being declared.
		M2AsmNode firstChild = (M2AsmNode) node.jjtGetChild(0);
		if (firstChild instanceof ASTDeclarator) {  // TODO DeclaratorNonInit
			int size = firstChild.value.equals("DB") ? 1 : Machine.WORD_SIZE;
			ASTValues valuesNode = (ASTValues) node.jjtGetChild(1);
			int numValues = valuesNode.jjtGetNumChildren();
			for (int i = 0; i < numValues; i++) {
				M2AsmNode valNode = (M2AsmNode) valuesNode.jjtGetChild(i);
				if (valNode instanceof ASTInteger || valNode instanceof ASTChar) {
					currDataAddress += size;
				}
				else if (valNode instanceof ASTStr) {
					currDataAddress += valNode.value.length();
				}
			}
		}
	}
}
