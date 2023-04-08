

import java.util.ArrayList;

public class Aresta {
	private Double peso;
	private Vertice<TIPO> inicio;
	private Vertice<TIPO> fim;


	public Aresta(Double peso, Vertice<TIPO> inicio, Vertice<TIPO> fim) {
		this.peso = peso;
		this.inicio = inicio;
		this.fim = fim;  

	}

	public Double getPeso() {
		return this.peso;
	}
	public void getPeso(Double peso) {
		this.peso = peso;
	}
	public Vertice<TIPO> getInicio() {
		return this.inicio;
	}
	public void setInicio(TIPO inicio) {
		this.inicio = inicio;
	}
	public Vertice<TIPO> getFim() {
		return this.fim;
	}
	public void setFim(TIPO fim) {
		this.fim = fim;
	}
 }