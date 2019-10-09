// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
  return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem > MaxPower || Elem < 0) throw "Index is out of range";
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem > MaxPower || Elem < 0) throw "Index is out of range";
	else BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem > MaxPower || Elem < 0) throw "Index is out of range";
	else BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (s != *this) {
		MaxPower = s.MaxPower;
		BitField = s.BitField;
	}
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if(BitField == s.BitField && MaxPower == s.MaxPower) return 1;
	else return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (BitField == s.BitField && MaxPower == s.MaxPower) return 0;
	else return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	return TSet(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem > MaxPower || Elem < 0) throw "Index is out of range";
	TSet temp(BitField);
	temp.BitField.SetBit(Elem);
	return temp.BitField;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet temp(*this);
	temp.BitField.ClrBit(Elem);
	return temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
  return TSet(~BitField);
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.BitField;
	return ostr;
}
