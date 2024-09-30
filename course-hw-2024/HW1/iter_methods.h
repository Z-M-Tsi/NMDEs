#ifndef ITER_METHODS_H
#define ITER_METHODS_H
#include <cmath>
#include<vector>

namespace iter 
{
    template<typename T>
    std::vector<T> newton(T (*f)(T), T (*f_diff)(T), T x0, T eps, int max_iter)
    {
        int iter;
        std::vector<T> roots;
        T x = x0, x_next;
        T res;
        for (iter = 0; iter < max_iter; iter++)
        {
            x_next = x - f(x) / f_diff(x);
            res = fabs(f(x_next));
            if (res < eps)
            {
                roots.push_back(x_next);
                std::cout << "Converged for x0 = " << x0 
                << " at round " << iter << "!"<< std::endl;
                std::cout << "Now x_previous = " << x
                << ", x_new = " << x_next << ", residual = " << res << "." << std::endl;
                return roots;
            }
            roots.push_back(x_next);
            x = x_next;
        }
        if (iter == max_iter) {
            std::cout << "After "<< max_iter << " iterations, the sequence did not converge for x0 = " 
            << x0 << "." << std::endl;
        }
        return roots;
    }

    template<typename T>
    std::vector<T> newton_down_hill(T (*f)(T), T (*f_diff)(T), T x0, T eps, int max_iter, T alpha)
    {
        int iter;
        std::vector<T> roots;
        T x = x0, x_next;
        T res;
        T gamma;

        for (iter = 0; iter < max_iter; iter++)
        {
            gamma = alpha;
            /* while (f(x - gamma*f(x) / f_diff(x)) - f(x) > eps)
            {
                gamma /= 2;
            } */
            x_next = x - gamma*f(x) / f_diff(x);
            res = fabs(f(x_next));
            if (res < eps)
            {
                roots.push_back(x_next);
                std::cout << "Converged for x0 = " << x0 
                << " at round " << iter << "!"<< std::endl;
                std::cout << "Now x_previous = " << x
                << ", x_new = " << x_next << ", residual = " << res << "." << std::endl;
                return roots;
            }
            roots.push_back(x_next);
            x = x_next;
        }
        if (iter == max_iter) {
            std::cout << "After "<< max_iter << " iterations, the sequence did not converge for x0 = " 
            << x0 << "." << std::endl;
        }
        return roots;
    }

    template<typename T>
    std::vector<T> iter_Aitken(T (*f)(T), T x0, T eps, int max_iter)
    {
        int iter;
        std::vector<T> roots;
        T x = x0, x_next;
        T y0, y1, y2;
        T res;

        roots.push_back(x);
        for (iter = 0; iter < max_iter; iter++)
        {
            y0 = x; y1 = f(y0); y2 = f(y1);
            x_next = (y0*y2-y1*y1)/(y2-2*y1+y0);
            T res = fabs(f(x_next));
            if (res < eps)
            {
                roots.push_back(x_next);
                std::cout << "Converged for x0 = " << x0 
                << " at round " << iter << "!"<< std::endl;
                std::cout << "Now x_previous = " << x
                << ", x_new = " << x_next << ", residual = " << res << "." << std::endl;
                return roots;
            }
            roots.push_back(x_next);
            x = x_next;
        }
        if (iter == max_iter) {
            std::cout << "After "<< max_iter << " iterations, the sequence did not converge for x0 = " 
            << x0 << "." << std::endl;
        }
        return roots;
    }
    
    template<typename T>
    std::vector<T> abs_errors(std::vector<T> xs, T x_star)
    {
        std::vector<T> errors(xs.size());
        for (int i = 0; i < xs.size(); i++) {
            errors[i] = fabs(xs[i] - x_star); 
        }
        return errors;
    }

    template<typename T>
    void error_order(std::vector<T> errors)
    {
        for (int i = 2; i < errors.size(); i++) {
            double p = std::log(errors[i] / errors[i - 1]) / std::log(errors[i - 1] / errors[i - 2]);
            
            if (errors.size() > 5000){
                if (i % 500 == 0)
                    std::cout << "Convergence order at step " << i << " = " << p << std::endl;
            }
            else if (errors.size() > 1000){
                if (i % 100 == 0)
                    std::cout << "Convergence order at step " << i << " = " << p << std::endl;
            }
            else if (errors.size() > 100){
                if (i % 10 == 0)
                    std::cout << "Convergence order at step " << i << " = " << p << std::endl;
            }
            else
            std::cout << "Convergence order at step " << i << " = " << p << std::endl;
        }
    }

}
#endif