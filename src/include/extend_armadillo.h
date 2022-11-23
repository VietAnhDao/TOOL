#include <armadillo>
#include <utility>
#include <math.h>
namespace arma
{
    arma::mat rot(double alpha, double beta, double gamma){
        arma::mat yaw(3,3, arma::fill::zeros);
        yaw(0,0) = std::cos(alpha);
        yaw(0,1) = -1.0*std::sin(alpha);
        yaw(1,0) = std::sin(alpha);
        yaw(1,1) = std::cos(alpha);
        yaw(2,2) = 1.0;

        arma::mat pitch(3,3, arma::fill::zeros);
        pitch(0,0) = std::cos(beta);
        pitch(0,2) = std::sin(beta);
        pitch(2,0) = -1.0*std::sin(beta);
        pitch(2,2) = std::cos(beta);
        pitch(1,1) = 1.0;

        arma::mat roll(3,3, arma::fill::zeros);
        roll(0,0) = 1.0;
        roll(1,1) = std::cos(gamma);
        roll(1,2) = -1.0*std::sin(gamma);
        roll(2,1) = std::sin(gamma);
        roll(2,2) = std::cos(gamma);

        arma::mat composit = yaw * pitch;
        composit = composit * roll;
        return composit;
    }
}
 