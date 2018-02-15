#include "zoo.h"

 int Animal::maisJovem = -1;

//----------------------------Veterinario----------------------------



string Veterinario::getNome() const {
	return nome;
}

//----------------------------Animal----------------------------

Animal::Animal(string nome, int idade)
{
	this->nome = nome;
	this->idade = idade;

	if (idade < Animal::maisJovem || Animal::maisJovem == -1)
		Animal::maisJovem = idade;
}


string Animal::getNome() const {
	return nome;
}

int Animal::getMaisJovem()
{
	return Animal::maisJovem;
}


//----------------------------Cao----------------------------

Cao::Cao(string nome, int idade, string raca) : Animal(nome,idade)
{
	this->raca = raca;
}


//----------------------------Voador----------------------------

Voador::Voador(int vmax, int amax)
{
	velocidade_max = vmax;
	altura_max = amax;
}

//----------------------------Morcego----------------------------

Morcego::Morcego(string nome, int idade, int vmax, int amax) : Animal(nome, idade), Voador(vmax, amax)
{
}

//----------------------------Zoo----------------------------


int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}
