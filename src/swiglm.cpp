#include <iostream>
#include "SWI-cpp.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


using namespace std;

template<class T> T read_term(term_t term);
template<> glm::mat4 read_term(term_t term);

template<class T> PlTerm construct_term(T& object);
template<> PlTerm construct_term(glm::mat4& matrix);

void print(glm::mat4 mat);
void print(glm::vec3 vec);
void print(glm::quat quat);

PREDICATE(print_matrix, 1)
{
	glm::mat4 load_matrix= read_term<glm::mat4>(A1);
	print(load_matrix);
	return TRUE;
}

PREDICATE(mul_matrix, 3)
{
	glm::mat4 left_matrix  = read_term<glm::mat4>(A1);
	glm::mat4 right_matrix = read_term<glm::mat4>(A2);
	
	glm::mat4 result = left_matrix * right_matrix;
	
	#ifdef DEBUG
		cout << "Begin multiplication" << endl;
		cout << "--------------------------" << endl;
		print(left_matrix);
		cout << "--------------------------" << endl;
		print(right_matrix);
		cout << "--------------------------" << endl;
		print(result);
		cout << "--------------------------" << endl;
		cout << "End multiplication" << endl;
	#endif

	return A3 = construct_term<glm::mat4>(result);
}

PREDICATE(convert_to_mat, 3)
{
	glm::vec3 translation = read_term<glm::vec3>(A1);
	glm::quat rotation    = read_term<glm::quat>(A2);

	glm::mat4 rotation_matrix    = glm::toMat4(rotation);
	glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), translation);

	glm::mat4 converted = translation_matrix * rotation_matrix;

	return A3 = construct_term<glm::mat4>(converted); 
}

template<class T>
T read_term(term_t term)
{
	T t;
	int index = 0;
	PlTerm element;
	PlTail tail(term);
	while(tail.next(element)) {
		t[index] = (double)(element);
		index++;
	}
	return t;
}

template<>
glm::mat4 read_term(term_t term)
{
	glm::mat4 mat(1.0f);

	PlTerm innerList;
	PlTail outerTail(term);
	int i = 0;
	while(outerTail.next(innerList)) {
		int j = 0;
		PlTerm element;
		PlTail innerTail(innerList);
		while(innerTail.next(element)) {
			mat[j][i] = (double)(element);
			j++;
		}
		i++;
	}
	return mat;
}

template<class T>
PlTerm construct_term(T& object)
{
	PlTerm term;
	PlTail tail(term);
	for (int i = 0; i < object.length(); ++i)
	{
		tail.append(object[i]);
	}
	tail.close();
	return term;
}

template<>
PlTerm construct_term(glm::mat4& matrix)
{
	PlTerm outerTerm;
	PlTail outerTail(outerTerm);
	for (int i = 0; i < 4; ++i)
	{
		PlTerm innerTerm;
		PlTail innerTail(innerTerm);
		for (int j = 0; j < 4; ++j)
		{
			innerTail.append(matrix[j][i]);
		}
		innerTail.close();
		outerTail.append(innerTerm);
	}
	outerTail.close();
	return outerTerm;
}

void print(glm::mat4 mat)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			cout << mat[j][i] << "\t";
		}
		cout << endl;
	}
}

void print(glm::vec3 vec)
{
	for (int i = 0; i < 3; ++i)
	{
		cout << vec[i];
	}
	cout << endl;
}

void print(glm::quat quat)
{
	for (int i = 0; i < 3; ++i)
	{
		cout << quat[i];
	}
	cout << endl;
}