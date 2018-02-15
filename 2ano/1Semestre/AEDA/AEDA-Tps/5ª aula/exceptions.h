#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <string>

class ClienteNaoExistente {
private:
	string nome;

public:
	ClienteNaoExistente(const string &nome)
	{
		this->nome = nome;
	}

	string getNome()
	{
		return this->nome;
	}

};



#endif /*EXCEPTIONS_H_*/