/*
    This file is part of Orange.

    Orange is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Orange is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Orange; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Authors: Janez Demsar, Blaz Zupan, 1996--2002
    Contact: janez.demsar@fri.uni-lj.si
*/


#ifndef __IMPUTATION_HPP
#define __IMPUTATION_HPP

#include "root.hpp"
#include "transval.hpp"
#include "classify.hpp"

WRAPPER(Imputer)
WRAPPER(ExampleGenerator)
WRAPPER(ImputerConstructor)
WRAPPER(Example)
WRAPPER(Learner)


class TTransformValue_IsDefined : public TTransformValue
{
public:
  __REGISTER_CLASS

  virtual void transform(TValue &val);
};


class TImputer : public TOrange
{
public:
  __REGISTER_ABSTRACT_CLASS
  virtual TExample *operator()(TExample &) = 0;

  virtual PExampleGenerator operator()(PExampleGenerator, const int &);

  void imputeDefaults(TExample *example, PExample defaults);
};


class TImputer_defaults : public TImputer
{
public:
  __REGISTER_CLASS
  PExample defaults; //P values that are to be inserted instead of missing ones

  TImputer_defaults(PDomain domain);
  TImputer_defaults(const TExample &example);
  virtual TExample *operator()(TExample &);
};


class TImputer_asValue : public TImputer
{
public:
  __REGISTER_CLASS
  PDomain domain; //P domain to which the values are converted
  PExample defaults; //P values to impute instead of missing ones - for continuous attributes only!
  virtual TExample *operator()(TExample &example);
};


class TImputer_model : public TImputer
{
public:
  __REGISTER_CLASS

  PClassifierList models;
  virtual TExample *operator()(TExample &example);
};


class TImputerConstructor : public TOrange
{
public:
  __REGISTER_ABSTRACT_CLASS

  bool imputeClass; //P tells whether to impute the class value (default: true)

  TImputerConstructor();
  virtual PImputer operator()(PExampleGenerator, const int &) = 0;
};


class TImputerConstructor_defaults : public TImputerConstructor
{
public:
  __REGISTER_CLASS
  PExample defaults; //P default values to be imputed instead missing ones

  virtual PImputer operator()(PExampleGenerator, const int &);
};

class TImputerConstructor_average : public TImputerConstructor
{
public:
  __REGISTER_CLASS
  virtual PImputer operator()(PExampleGenerator, const int &);
};


class TImputerConstructor_minimal : public TImputerConstructor
{
public:
  __REGISTER_CLASS
  virtual PImputer operator()(PExampleGenerator, const int &);
};


class TImputerConstructor_maximal : public TImputerConstructor
{
public:
  __REGISTER_CLASS
  virtual PImputer operator()(PExampleGenerator, const int &);
};


class TImputerConstructor_asValue : public TImputerConstructor
{
public:
  __REGISTER_CLASS
  virtual PImputer operator()(PExampleGenerator, const int &);

  PVariable createImputedVar(PVariable);
};


WRAPPER(Learner)
class TImputerConstructor_model : public TImputerConstructor
{
public:
  __REGISTER_CLASS
  PLearner learnerDiscrete; //P learner for discrete attributes
  PLearner learnerContinuous; //P learner for continuous attributes

  bool useClass; //P tells whether to use class value in imputation (default: false)

  TImputerConstructor_model();
  virtual PImputer operator()(PExampleGenerator, const int &);
};

#endif