#include <iostream>
using namespace std;

// 定义微分方程的接口
class DifferentialEquation {
public:
    virtual double evaluate(double x, double y) = 0;
};

// 实现微分方程的接口，即实现具体的一阶常微分方程
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

//定义解微分方程方法的接口
class SolveDifferentialEquationMethod {
public:
    virtual double solve(DifferentialEquation& equation, double x0, double y0, double step, double x_target) = 0;
};

// 实现解微分方程方法的接口，定义Euler方法
class EulerMethod : SolveDifferentialEquationMethod {
public:
    double solve(DifferentialEquation& equation, double x0, double y0, double step, double x_target) {
        double x = x0;
        double y = y0;
        while (x < x_target) {
            y += equation.evaluate(x, y) * step; // Euler方法的迭代公式
            x += step;
        }
        return y;
    }
};

// 实现解微分方程方法的接口，定义RungeKutta方法
class RungeKuttaMethod : SolveDifferentialEquationMethod {
public:
    double solve(DifferentialEquation& equation, double x0, double y0, double h, double x) {
        int n = (int)((x - x0) / h);
        float k1, k2, k3, k4, k5;
        float y = y0;
        for (int i = 1; i <= n; i++) { //RungeKutta迭代公式
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
    // 设置初始条件和参数
    double x0 = 0.0; //自变量初始值
    double y0 = 1.0; //因变量在起始点的初始值。
    double step = 0.1; //步长
    double x_target = 1.0; //求解微分方程的目标点，即x在这点上y的值

    // 创建微分方程对象和数值解方法对象
    MyDifferentialEquation1 equation1;
    MyDifferentialEquation2 equation2;
    EulerMethod euler;
    RungeKuttaMethod rungeKutta;

    // 使用Euler方法求解微分方程的数值解
    double numerical_solution1 = euler.solve(equation1, x0, y0, step, x_target);
    double numerical_solution2 = euler.solve(equation2, x0, y0, step, x_target);
    // 使用RungeKutta方法求解微分方程的数值解
    double numerical_solution3 = rungeKutta.solve(equation1, x0, y0, step, x_target);
    double numerical_solution4 = rungeKutta.solve(equation2, x0, y0, step, x_target);

    // 输出结果
    cout << "第一个方程用Euler方法在 " << x_target << " 的y值是： " << numerical_solution1 << endl;
    cout << "第二个方程用Euler方法在 " << x_target << " 的y值是： " << numerical_solution2 << endl;
    cout << "第一个方程用RungeKutta方法在 " << x_target << " 的y值是： " << numerical_solution3 << endl;
    cout << "第二个方程用RungeKutta方法在 " << x_target << " 的y值是： " << numerical_solution4 << endl;

    return 0;
}
