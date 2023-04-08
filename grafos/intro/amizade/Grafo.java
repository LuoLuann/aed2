
import java.util.ArrayList;

//esse tipo eh o dado qualquer que iremos passar
public class Grafo<TIPO> {
	private ArrayList<Vertice<TIPO>> vertices;
	private ArrayList<Aresta<TIPO>> arestas;


	public Grafo() {
		this.vertices = new ArrayList <Vertice<TIPO>>();
		this.arestas = new ArrayList<Vertice<TIPO>>();
	}

	public void adicionarVertice(TIPO dado) {
		Vertice<TIPO> novoVertice = new Vertie<TIPO>(dado);
		//agora add ao grafo esse novo vertice criado
		this.vertices.add(novoVertice);
	}
	//seria como se passassemos uma aresta entre duas pessoas
	//com um peso definindo uma relação entre elas
	public void adicionarAresta(Double peso, TIPO dadoInicio, TIPO dadoFim) {
		 Vertice<TIPO> inicio = this.getVertice(dadoInicio);
		 Vertice<TIPO> fim = this.getVertice(dadoFim);

		 Aresta<TIPO> aresta = new Aresta<TIPO>(peso, inicio, fim);
		 inicio.adicionarArestaSaida(aresta);
		 fim.adicionarArestaEntrada(aresta);

		 this.aresta.add(aresta);
	}
	public Vertice<TIPO> getVertice(TIPO dado) {
		Vertice<TIPO> vertice =  null;
		//percorrer toda lista de vertices do grafo
		for(int i = 0; i < this.vertices.size(); i++) {
			if(this.vertices.get(i).getDado().equals(dado)) {
				vertice = this.vertices.get(i);
				break;
			}
		}
		return vertice;
	}
}