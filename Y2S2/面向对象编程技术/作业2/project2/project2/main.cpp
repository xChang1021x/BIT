#include <iostream>
using namespace std;

// ����΢�ַ��̵Ľӿ�
class DifferentialEquation {
public:
    virtual double evaluate(double x, double y) = 0;
};

// ʵ��΢�ַ��̵Ľӿڣ���ʵ�־����һ�׳�΢�ַ���
class MyDifferentialEquation1 : public DifferentialEquation {
public:
    double evaluate(double x, double y) {
        return x + y; // dy/dx = x + y
    }
};

class MyDifferentialEquation2 : public DifferentialEquation {
public:
    double evaluate(double x, double y) {
        return 2 * x - y; // dy/dx = 2x - y
    }
};

//�����΢�ַ��̷����Ľӿ�
class SolveDifferentialEquationMethod {
public:
    virtual double solve(DifferentialEquation& equation, double x0, double y0, double step, double x_target) = 0;
};

// ʵ�ֽ�΢�ַ��̷����Ľӿڣ�����Euler����
class EulerMethod : SolveDifferentialEquationMethod {
public:
    double solve(DifferentialEquation& equation, double x0, double y0, double step, double x_target) {
        double x = x0;
        double y = y0;
        while (x < x_target) {
            y += equation.evaluate(x, y) * step; // Euler�����ĵ�����ʽ
            x += step;
        }
        return y;
    }
};

// ʵ�ֽ�΢�ַ��̷����Ľӿڣ�����RungeKutta����
class RungeKuttaMethod : SolveDifferentialEquationMethod {
public:
    double solve(DifferentialEquation& equation, double x0, double y0, double h, double x) {
        int n = (int)((x - x0) / h);
        float k1, k2, k3, k4, k5;
        float y = y0;
        for (int i = 1; i <= n; i++) { //RungeKutta������ʽ
            k1 = h * equation.evaluate(x0, y);
            k2 = h * equation.evaluate(x0 + 0.5 * h, y + 0.5 * k1);
            k3 = h * equation.evaluate(x0 + 0.5 * h, y + 0.5 * k2);
            k4 = h * equation.evaluate(x0 + h, y + k3);

            y = y + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);;

            x0 = x0 + h;
        }
        return y;
    }
};

int main() {
    // ���ó�ʼ�����Ͳ���
    double x0 = 0.0; //�Ա�����ʼֵ
    double y0 = 1.0; //���������ʼ��ĳ�ʼֵ��
    double step = 0.1; //����
    double x_target = 1.0; //���΢�ַ��̵�Ŀ��㣬��x�������y��ֵ

    // ����΢�ַ��̶������ֵ�ⷽ������
    MyDifferentialEquation1 equation1;
    MyDifferentialEquation2 equation2;
    EulerMethod euler;
    RungeKuttaMethod rungeKutta;

    // ʹ��Euler�������΢�ַ��̵���ֵ��
    double numerical_solution1 = euler.solve(equation1, x0, y0, step, x_target);
    double numerical_solution2 = euler.solve(equation2, x0, y0, step, x_target);
    // ʹ��RungeKutta�������΢�ַ��̵���ֵ��
    double numerical_solution3 = rungeKutta.solve(equation1, x0, y0, step, x_target);
    double numerical_solution4 = rungeKutta.solve(equation2, x0, y0, step, x_target);

    // ������
    cout << "��һ��������Euler������ " << x_target << " ��yֵ�ǣ� " << numerical_solution1 << endl;
    cout << "�ڶ���������Euler������ " << x_target << " ��yֵ�ǣ� " << numerical_solution2 << endl;
    cout << "��һ��������RungeKutta������ " << x_target << " ��yֵ�ǣ� " << numerical_solution3 << endl;
    cout << "�ڶ���������RungeKutta������ " << x_target << " ��yֵ�ǣ� " << numerical_solution4 << endl;

    return 0;
}
