#include "login.h"
#include "patient information.h"
#include "dosage.h"
#include "cpr.h"

int main() {
    if (login() == 1) {
        EnterCPR();
        dosageCalculator();
    }
    return 0;
}