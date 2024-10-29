//input values: velocity, brake pedal, transmission, wiperSpeed, wiperInterval
//output values: stopWiping, startWiping, setWiperSpeed, setWiperInterval
#include <cmath> // Required for fabs()

enum sonarType
{
    DETECTED = 1
};
enum transmissionType
{
    TO_CHECK = -9,
    PARK = -1,
    DRIVE = 1,
    MANUAL = 2
};
bool vehPedalType = true;
transmissionType transmissionValue = DRIVE;

void executeParkingCase(sonarType sonarValue, transmissionType transmissionValue)
{   
    if (sonarValue!= DETECTED && transmissionValue == PARK)
    {
        stopWiping();
    }
    else 
    {
        startWiping();
    }
}
bool isValueZeroForThreeSeconds() {
    const double duration = 3.0; // seconds
    const double checkInterval = 0.1; // seconds between checks
    double timeZero = 0.0;

    while (timeZero < duration) {
        double velocity = getVelocity();

        if (velocity == 0.0) {
            timeZero += checkInterval;
        } else {
            timeZero = 0.0; // Reset if `a` is not 0
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(checkInterval * 1000)));
    }

    return true; // `velocity` was 0 for the full 3 seconds
}
bool executeDefaultCase(double vehVelocityValue, bool vehPedalValue, transmissionType transmissionValue)
{
    bool stopStatus = 0;
    bool drivingIntention = 0;
    stopStatus = isValueZeroForThreeSeconds();
    drivingIntention = ((transmissionValue == DRIVE || transmissionValue == MANUAL) && vehPedalValue == 0);

    if((stopStatus == true && drivingIntention != true) || transmissionValue == TO_CHECK)
    {
        stopWiping();
    }
    else 
    {
        startWiping();
    }

}
void setWiperValue(double vehVelocityValue, double refVehVelocityValue,double refWiperSpeed, double refWiperInterval)
{
    const int divider = 5;
    double diff = vehVelocityValue - refVehVelocityValue;
    double diffDivided = diff / divider; 
    int output_1;
    if (diffDivided < 0) {
    output_1 = -1;
    } else if (diffDivided == 0) {
        output_1 = 0;
    } else if (diffDivided > 0) {
        output_1 = 1;
    }
    double output_2 = std::floor(fabs(diffDivided))*0.1;
    double output_3 = output_1 * output_2 + 1;
    setWiperSpeed(std::round(output_3 * refWiperSpeed));
    setWiperInterval(std::round(output_3 *refWiperInterval));

}
void wiperControlRefGen(double vehVelocityValue, double wiperSpeed, double wiperInterval)
{
    //if(detectWiperValue())
    {//사용자가 값을 바꿨을 경우
        double refVehVelocityValue = vehVelocityValue;
        double refWiperSpeed = wiperSpeed;
        double refWiperInterval = wiperInterval;

        setWiperValue(vehVelocityValue, refVehVelocityValue, refWiperSpeed, refWiperInterval);
    }

}

main()
{
    if (transmissionValue == PARK)
    {
        bool stopStatus = executeParkingCase(sonarValue, transmissionValue);
    }
    else
    {
        executeDefaultCase(vehVelocityValue, vehPedalValue, transmissionValue);
    }

    wiperControlRefGen(vehVelocityValue, wiperSpeed, wiperInterval);
}