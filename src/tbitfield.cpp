// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <string>

TBitField::TBitField(int len)
{
	if (len < 0) throw "Index is out of range";
	else {
		BitLen = len;
		MemLen = (len-1)/(8*sizeof(TELEM)) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n >= BitLen) throw "Index is out of range";
	else return n>>5;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n >= BitLen) throw "Index is out of range";
	else {
		TELEM m = 1 << (n % ((sizeof(TELEM) * 8)));
		return m;
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen) throw "Index is out of range";
	else {
		int i = GetMemIndex(n);
		pMem[i] |= GetMemMask(n);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen) throw "Index is out of range";
	else {
		int i = GetMemIndex(n);
		pMem[i] &= ~GetMemMask(n);
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen) throw "Index is out of range";
	else {
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf) {
		MemLen = bf.MemLen;
		BitLen = bf.BitLen;
		delete[] pMem;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++) pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 0;
	else {
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i]) return 0;
		}
		return 1;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 1;
	else {
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i]) return 1;
		}
		return 0;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int length = BitLen;
	if (bf.BitLen > BitLen) length = bf.BitLen;
	TBitField temp(length);

	for (int i = 0; i < MemLen; i++) temp.pMem[i] = pMem[i] | bf.pMem[i];
	for (int i = MemLen; i < bf.MemLen; i++) temp.pMem[i] = bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int length = BitLen;
	if (bf.BitLen > BitLen) length = bf.BitLen;
	TBitField temp(length);

	for (int i = 0; i < MemLen; i++) temp.pMem[i] = pMem[i] & bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(*this);
	for (int i = 0; i < BitLen; i++) {
		if (temp.GetBit(i)) temp.ClrBit(i);
		else temp.SetBit(i);
	}

	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string str;
	istr >> str;
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (str[i] == '1')
			bf.SetBit(i);
		else if (str[i] == '0')
			bf.ClrBit(i);
	}

	return istr;
}


ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for(int i = 0; i < bf.BitLen; i++) ostr << bf.GetBit(i);
	return ostr;
}
