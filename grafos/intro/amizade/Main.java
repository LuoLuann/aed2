
public class Main {

	public static void Main(String[] args) {
		Grafo<String> grafo = new Grafo<String>();

		grafo.adicionarVertice("Luann");
		grafo.adicionarVertice("Nath");
		grafo.adicionarVertice("Joanne");
		grafo.adicionarVertice("Thiago");
		grafo.adicionarVertice("Liandro");


		grafo.adicionarAresta(2.00, "Luann", "Nath");
		grafo.adicionarAresta(5.00, "Thiago", "Luann");
		grafo.adicionarAresta(6.00, "Joanne", "Nath");
		grafo.adicionarAresta(3.00, "Liandro", "Thiago");
	}
}