#pragma once

#include <iostream>
#include <string>

#include "Eigen/Dense"
#include "multiThreading.h"

using namespace Eigen;
using namespace std;

inline void oving9Task() {
    cout << "Task 5c from assignment 9 with Eigen\n";

    Matrix2d A, B, C;

    A << 1.0, 2.0,  //
        3.0, 4.0;   //

    B << 4.0, 3.0,  //
        2.0, 1.0;   //

    C << 1.0, 3.0,  //
        1.5, 2.0;   //

    cout << "\nBefore calculation:\n";
    cout << "Matrix A:\n" << A << "\n";
    cout << "Matrix B:\n" << B << "\n";
    cout << "Matrix C:\n" << C << "\n";

    A += B + C;

    cout << "\nAfter A += B + C:\n";
    cout << "Matrix A:\n" << A << "\n";
    cout << "Matrix B:\n" << B << "\n";
    cout << "Matrix C:\n" << C << "\n";
}

inline void matrixClass() {
    int input = 1;
    while (input) {
        cout << "\n" << string(40, '-') << "\n";
        cout << "0) Exit\n";
        cout << "1) Comma-initialization\n";
        cout << "2) Scalar multiplication and division\n";
        input = getIntInput(0, 2);
        switch (input) {
            case 1: {
                MatrixXd m(2, 2);
                m(0, 0) = 3;
                m(1, 0) = 2.5;
                m(0, 1) = -1;
                m(1, 1) = m(1, 0) + m(0, 1);
                cout << "Here is the matrix m:\n" << m << endl;
                VectorXd v(2);
                v(0) = 4;
                v(1) = v(0) - 1;
                cout << "Here is the vector v:\n" << v << endl;
                break;
            }
            case 2: {
                Matrix3f m;
                m << 1, 2, 3,  //
                    4, 5, 6,   //
                    7, 8, 9;   //
                cout << m;
                break;
            }
            default:
                break;
        }
    }
}

inline void arithmetic() {
    int input = 1;
    while (input) {
        cout << "\n" << string(40, '-') << "\n";
        cout << "0) Exit\n";
        cout << "1) Addition and subtraction\n";
        cout << "2) Scalar multiplication and division\n";
        cout << "3) Matrix-matrix and matrix-vector multiplication\n";
        cout << "4) Dot product and cross product\n";
        cout << "5) Basic arithmetic reduction operations\n";
        input = getIntInput(0, 5);
        switch (input) {
            case 1: {
                Matrix2d a;
                a << 1, 2, 3, 4;
                MatrixXd b(2, 2);
                b << 2, 3, 1, 4;

                cout << "a:\n" << a << endl;
                cout << "b:\n" << b << endl;
                cout << "a + b =\n" << a + b << endl;
                cout << "a - b =\n" << a - b << endl;
                cout << "Doing a += b;" << endl;
                a += b;
                cout << "Now a =\n" << a << endl;

                Vector3d v(1, 2, 3);
                Vector3d w(1, 0, 0);

                cout << "v:\n" << v << endl;
                cout << "w:\n" << w << endl;
                cout << "-v + w - v =\n" << -v + w - v << endl;
                break;
            }
            case 2: {
                Matrix2d a;
                a << 1, 2,  //
                    3, 4;   //
                Vector3d v(1, 2, 3);

                cout << "a:\n" << a << endl;
                cout << "v:\n" << v << endl;
                cout << "a * 2.5 =\n" << a * 2.5 << endl;
                cout << "0.1 * v =\n" << 0.1 * v << endl;
                cout << "Doing v *= 2;" << endl;
                v *= 2;
                cout << "Now v =\n" << v << endl;
                break;
            }
            case 3: {
                Matrix2d mat;
                mat << 1, 2, 3, 4;
                Vector2d u(-1, 1), v(2, 0);

                cout << "mat:\n" << mat << endl;
                cout << "u:\n" << u << endl;
                cout << "v:\n" << v << endl;
                cout << "Here is mat*mat:\n" << mat * mat << endl;
                cout << "Here is mat*u:\n" << mat * u << endl;
                cout << "Here is u^T*mat:\n" << u.transpose() * mat << endl;
                cout << "Here is u^T*v:\n" << u.transpose() * v << endl;
                cout << "Here is u*v^T:\n" << u * v.transpose() << endl;
                cout << "Let's multiply mat by itself" << endl;
                mat = mat * mat;
                cout << "Now mat is mat:\n" << mat << endl;
                break;
            }
            case 4: {
                Vector3d v(1, 2, 3);
                Vector3d w(0, 1, 2);

                cout << "v:\n" << v << endl;
                cout << "w:\n" << w << endl;
                cout << "Dot product: " << v.dot(w) << endl;
                cout << "Cross product:\n" << v.cross(w) << endl;
                break;
            }
            case 5: {
                Eigen::Matrix2d mat;
                mat << 1, 2,  //
                    3, 4;     //

                cout << "mat:\n" << mat << endl;
                cout << "Here is mat.sum():       " << mat.sum() << endl;
                cout << "Here is mat.prod():      " << mat.prod() << endl;
                cout << "Here is mat.mean():      " << mat.mean() << endl;
                cout << "Here is mat.minCoeff():  " << mat.minCoeff() << endl;
                cout << "Here is mat.maxCoeff():  " << mat.maxCoeff() << endl;
                cout << "Here is mat.trace():     " << mat.trace() << endl;
                break;
            }
            default:
                break;
        }
    }
}

inline void linearSolving() {
    int input = 1;
    while (input) {
        cout << "\n" << string(40, '-') << "\n";
        cout << "0) Exit\n";
        cout << "1) Basic linear solving\n";
        cout << "2) Computing eigenvalues and eigenvectors\n";
        cout << "3) Computing inverse and determinant\n";
        input = getIntInput(0, 3);
        switch (input) {
            case 1: {
                Matrix3f A;
                Vector3f b;
                A << 1, 2, 3,  //
                    4, 5, 6,   //
                    7, 8, 10;  //
                b << 3, 3, 4;

                cout << "Here is the matrix A:\n" << A << endl;
                cout << "Here is the vector b:\n" << b << endl;
                Vector3f x = A.colPivHouseholderQr().solve(b);
                cout << "The solution is:\n" << x << endl;
                break;
            }
            case 2: {
                Matrix2f A;
                A << 1, 2,  //
                    2, 3;   //

                cout << "Here is the matrix A:\n" << A << endl;
                SelfAdjointEigenSolver<Matrix2f> eigensolver(A);
                if (eigensolver.info() != Success) abort();
                cout << "The eigenvalues of A are:\n"
                     << eigensolver.eigenvalues() << endl;
                cout << "Here's a matrix whose columns are eigenvectors of A \n"
                     << "corresponding to these eigenvalues:\n"
                     << eigensolver.eigenvectors() << endl;
                break;
            }
            case 3: {
                Matrix3f A;
                A << 1, 2, 1,  //
                    2, 1, 0,   //
                    -1, 1, 2;  //

                cout << "Here is the matrix A:\n" << A << endl;
                cout << "The determinant of A is " << A.determinant() << endl;
                cout << "The inverse of A is:\n" << A.inverse() << endl;
                break;
            }
            default:
                break;
        }
    }
}

inline void showEigenUsage() {
    int input = 1;
    while (input) {
        cout << "\n" << string(40, '-') << "\n";
        cout << "0) Exit\n";
        cout << "1) oving9Task()\n";
        cout << "2) matrixClass()\n";
        cout << "3) arithmetic()\n";
        cout << "4) linearSolving()\n";
        input = getIntInput(0, 4);
        switch (input) {
            case 1: {
                oving9Task();
                break;
            }
            case 2: {
                matrixClass();
                break;
            }
            case 3: {
                arithmetic();
                break;
            }
            case 4: {
                linearSolving();
                break;
            }
            default:
                break;
        }
    }
}
