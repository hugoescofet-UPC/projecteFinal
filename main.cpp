
#include <iostream>
#include <string>
#include <vector>
#include <functional>
using namespace std;


// Publicacion y sus tipos (Polimorfismo)
class Publicacion {
protected:
	int likes;
	string fecha;
public:
	explicit Publicacion(int likesI, string fechaI) :
		likes(likesI), fecha(fechaI) {
	}
	virtual void getDatos() const = 0;
};

class Estado : public Publicacion {
private:
	int caracteres;
public:
	explicit Estado(int likesI, string fechaI, int caracteresI) : Publicacion(likesI, fechaI), caracteres(caracteresI);

	void getDatos() const override {
		cout << "Caracteres: " << caracteres << "\nLikes: " << likes << "\t" << fecha << endl;
	}
};

class Historia : public Publicacion {
private:
	int duracion;
	string musica;
public:
	explicit Historia(int likesI, string fechaI, int duracionI, string musicaI) : Publicacion(likesI, fechaI), duracion(duracionI), musica(musicaI);

	void getDatos() const override {
		cout << "Musica: " << musica << "\nLikes: " << likes << "\tDuracion: " << duracion << "\t" << fecha << endl;
	}
};

class Carrusel : public Publicacion {
private:
	string hashtags;
	int cantidad;
public:
	explicit Carrusel(int likesI, string fechaI, string hashtagsI, int cantidadI) : Publicacion(likesI, fechaI), hashtags(hashtagsI), cantidad(cantidadI);

	void getDatos() const override {
		cout << "Cantidad: " << cantidad << "\nLikes: " << likes << "\t" << fecha << "\n" << hashtags;
	}
};


class Perfil {
private:
	string nombre;
	int seguidores;
	int seguidos;
	vector <Estado> estados;
	vector <Historia> historias;
	vector <Carrusel> carruseles;
public:
	explicit Perfil(string m = "undefined", int seguidores = 0, int seguidos = 0) : nombre(m), seguidores(seguidores), seguidos(seguidos) {}

	string getNombre() const { return nombre; }
	int getSeguidores() const { return seguidores; }
	int getSeguidos() const { return seguidos; }

	void cambiarNombre(string nuevoNombre) { nombre = nuevoNombre; }

	void consultarPublicacion(const Publicacion& publi) const {
		publi.getDatos();
	}

	void añadirEstado(int l, string f, int c)
	{
		estados.emplace_back(l, f, c);
	}

	void añadirHistoria(int l, string f, int d, string m)
	{
		estados.emplace_back(l, f, d, m);
	}

	void añadirCarrusel(int l, string f, string h, int c)
	{
		estados.emplace_back(l, f, h, c);
	}

	void mostrarPublicaciones() const {
		for (const auto& e : estados) {
			cout << "Estado" << endl;
			cout << "- " << e.getDatos() << endl;
		}
		for (const auto& h : historias) {
			cout << "Historia" << endl;
			cout << "- " << h.getDatos() << endl;
		}
		for (const auto& c : carruseles) {
			cout << "Carrusel" << endl;
			cout << "- " << c.getDatos() << endl;
		}


	};


	class Usuario {
	private:
		string correo;
		string ubicacion;
		vector <Perfil> perfils; //COMPO 1:N
	public:
		explicit Usuario(string correo, string ubicacion, string m, int seguidoresI, int seguidosI) : correo(correo), ubicacion(ubicacion) {
			perfils.emplace_back(m, seguidoresI, seguidosI);
		}

		string getCorreo() const { return correo; }
		string getUbicacion() const { return ubicacion; }

		void añadirPerfil(string nombreP, int seguidoresP, int seguidosP)
		{
			perfils.emplace_back(nombreP, seguidoresP, seguidosP);
		}

		void listarPerfiles() const {
			for (const auto& p : perfils) {
				cout << "Perfil" << endl;
				cout << "- " << p.getNombre() << endl;
				cout << "- " << p.getSeguidores() << endl;
				cout << "- " << p.getSeguidos() << endl;
			}
		}
	};


	class Comunidad {
	private:
		vector <reference_wrapper <Perfil>> perfils; //AGREGACIO 1:N
		Perfil& propietario; //AGREGACIO 1:1
	public:
		explicit Comunidad(Perfil& prop) : propietario(prop) {}

		void entrarPerfil(Perfil& p) { perfils.push_back(p); }
		void listaPerfiles() const{
			for (const Perfil& p : perfils) {
		cout << "Perfil" << endl;
					cout << "- " << p.getNombre() << endl;
					cout << "- " << p.getSeguidores() << endl;
					cout << "- " << p.getSeguidos() << endl;
				}
		}
			void cambiarPropietario(Perfil& nuevoPropietario)
		{
			propietario = nuevoPropietario;
		}
	};