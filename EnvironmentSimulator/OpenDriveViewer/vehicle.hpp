
class Vehicle
{
public:
	Vehicle(double x, double y, double h, double length);
	void Update(double dt, int acceleration, int steering);
	void SetWheelAngle(double angle);
	void SetWheelRotation(double rotation);
	void SetPos(double x, double y, double z, double h)
	{
		posX_ = x;
		posY_ = y;
		posZ_ = z;
		heading_ = h;
	}

	double posX_;
	double posY_;
	double posZ_;
	double heading_;
	double pitch_;

	double velX_;
	double velY_;
	double velAngle_;
	double velAngleRelVehicleLongAxis_;
	double speed_;
	double wheelAngle_;
	double wheelRotation_;
	double headingDot_;

	double length_;
};
