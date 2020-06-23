/**
 * \file Exceptions.h
 * \author Emily Horsman <horsmane@mcmaster.ca>
 * \brief Provides all exception declarations from the specification.
 */
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class invalid_capacity : public std::exception {
   const char * what () const throw () {
      return "invalid capacity";
   }
};

class full : public std::exception {
   const char * what () const throw () {
      return "full";
   }
};

class empty : public std::exception {
   const char * what () const throw () {
      return "empty";
   }
};

class invalid_placement : public std::exception {
   const char * what () const throw () {
      return "invalid placement";
   }
};

class invalid_move : public std::exception {
   const char * what () const throw () {
      return "invalid move";
   }
};

class empty_source : public std::exception {
   const char * what () const throw () {
      return "empty source";
   }
};

#endif
