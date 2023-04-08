
import java.util.ArrayList;

public class Vertice<TIPO> {
	private TIPO dado;
	//esse tipo dado eh uma pessoa

	//todo grafico direcional precisa de umma lista
	//de arestas de entrada e de saida
	private ArrayList<Aresta<TIPO>> arestasEntrada;
	private ArrayList<Aresta<TIPO>> arestasSaida;

	Vertice(TIPO valor) {
		this.dado = valor;
		this.arestasEntrada = new ArrayList<Aresta<TIPO>>();
		this.arestasSaida = new ArrayList<Aresta<TIPO>>();
	}

	public TIPO getDado() {
		return dado;
	}
	public void setDado(TIPO dado) {
		this.dado = dado;
	}

	public void adicionarArestaEntrada(Aresta<TIPO> aresta) {
		this.arestasEntrada.add(aresta);
	}
	public void adicionarArestaSaida(Aresta<TIPO> aresta) {
		this.arestasSaida.add(aresta);
	}

}