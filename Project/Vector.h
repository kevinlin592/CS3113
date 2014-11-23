Vector::Vector(){
	x = 1.0f;
	y = 1.0f;
	z = 1.0f;
	normalize();
}

Vector::Vector(float a, float b, float c){
	x = a;
	y = b;
	z = c;
}

float Vector::length(){
	return sqrtf(x*x + y*y + z*z);
}

void Vector::normalize(){
	float dist = length();
	x /= dist;
	y /= dist;
	z /= dist;
}