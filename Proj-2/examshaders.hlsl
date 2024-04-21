#define COUNT 1000
#define PI 3.14159265
#define MaxError 0.0001
#define MaxDistance 1000.0

cbuffer Constant
{
	float4 viewPoint;
	float4 lightColor;
	float4 upDirection;
	float4 lightPosition;
	float4 rightDirection;
	float4 forwardDirection;

	float4 colors[COUNT];
	float4 positions[COUNT];
	float4 triangles[COUNT];
};

float3 InterpolateVector(float3 t, float3 v0, float3 v1, float3 v2)
{
	return v0*t.x+v1*t.y+v2*t.z;
}

// area = 1/2 * | (b-a) X (c-a) |
float area(float3 p1, float3 p2, float3 p3) {
	return 0.5 * length(cross(p2 - p1, p3 - p1));
}

// o = origin, d = direction
float4 IntersectTriangle(float3 p1, float3 p2, float3 p3, float3 o, float3 d)
{
	/*
		solve plane equation Ax+By+Cz+D=0
		which intersects with ray p(t)=o+d*t
		solve the t as the distance:

			t=-(dot(n, o)+w)/dot(n, d),
			where w=-dot(n, p1)

		if t<MaxError: there is no intersection

		calculate area of triangle p1 p2 p3 as S
		calculate area of triangle p p2 p3 as S1
		calculate area of triangle p1 p p3 as S2
		calculate area of triangle p1 p2 p as S3
		if S1+S2+S3>S+MaxError: there is no intersection

		Otherwsie: return  float4(S1/S, S2/S, S3/S, t);
	*/
	float4 noIntersection=float4(0, 0, 0, MaxDistance);
	float3 normal = normalize(cross(p2 - p1, p3 - p1));
	float w = -dot(normal, p1);
	float t = -(dot(normal, o) + w) / dot(normal, d);

	if (t < MaxError) return noIntersection;

	float3 p = o + t * d;
	float S = area(p1, p2, p3);
	float S1 = area(p, p2, p3);
	float S2 = area(p1, p, p3);
	float S3 = area(p1, p2, p);

	if (S1 + S2 + S3 > S + MaxError) return noIntersection;

	//float3 n = normalize(cross(p1 - p0, p2 - p0););
	//float

	return float4(S1 / S, S2 / S, S3 / S, t);
}

// Call this function to intersect the ray with the i th traingle in the scene
float4 IntersectTriangle(uint i, float3 origin, float3 direction)
{
	uint i0=uint(triangles[i].x), i1=uint(triangles[i].y), i2=uint(triangles[i].z);
	float3 p0=positions[i0].xyz, p1=positions[i1].xyz, p2=positions[i2].xyz;
	return IntersectTriangle(p0, p1, p2, origin, direction);
}

 // Calculate the nearest intersection between ray and traingles
float4 IntersectTriangles(float3 origin, float3 direction)
{
	// Reminder: triangles[0].w specifies how many triangles in total
	/*
		Given a ray with origin and direction as input
		find the nearest intersection among all of the traingles 
		in the scene as the output. intersection Format is:
		Barycentric Coord is (a, b, c)=(S1, S2, S3)/S
		Result: float4 nearestIntersection = { a, b, c, distance} 
		where distance is t
	*/
	float4 nearestIntersection = float4(0, 0, 0, MaxDistance);

	float minDistance = MaxDistance;
	int nearestIndex = -1; 

	uint count = uint(triangles[0].w);
	for (uint i = 0; i < count; i++) {
		float4 intersection = IntersectTriangle(i, origin, direction);
		float distance = intersection.w;
		if (distance < minDistance) {
			nearestIntersection = intersection;
			nearestIndex = i;
			minDistance = distance;
		}
	}
	//before return, update distance t into nearest triangle index; 
	// nearestIndex=-1 means no intersection is found
	nearestIntersection.w = nearestIndex;  
	return nearestIntersection;
}

 // Interpolate color or position at an intersection using Barycentric coord
float3 Interpolate(float4 intersection, bool isColor)
{
	uint i=int(intersection.w), i0=uint(triangles[i].x), i1=uint(triangles[i].y), i2=uint(triangles[i].z);
	return isColor?InterpolateVector(intersection.xyz, colors[i0].xyz, colors[i1].xyz, colors[i2].xyz):
	InterpolateVector(intersection.xyz, positions[i0].xyz, positions[i1].xyz, positions[i2].xyz);
}

float3 GetNormal(float4 intersection)  // Calculate normal direction at the intersection
{
	uint i=int(intersection.w); uint i0=uint(triangles[i].x), i1=uint(triangles[i].y), i2=uint(triangles[i].z);
	float3 p0=positions[i0].xyz, p1=positions[i1].xyz, p2=positions[i2].xyz; return normalize(cross(p1-p0, p2-p0));
}

int GetShadow(float3 position, float3 lightDirection)
{
	float3 o=position, d=lightDirection;
	float4 intersection=IntersectTriangles(o, d);
	return int(intersection.w)==-1?0:1; 
	// intersection.w==-1: there is no intersection, it can see light at position p,  p is not on shadow
	// Otherwise; there is intersection with triangles and it can't see light at position p, p is on shadow
}

float3 ViewDirection(float3 inputPosition)
{
	float3 eyeCenter=viewPoint.xyz; float viewFocus=viewPoint.w;
	float3 focus=eyeCenter+viewFocus*forwardDirection.xyz;
	float3 rightOffset=inputPosition.x*rightDirection.xyz;
	float3 upOffset=inputPosition.y*upDirection.xyz;
	float3 viewCenter=focus+rightOffset+upOffset;
	return normalize(viewCenter-eyeCenter);
}

float4 GetColor(float4 intersection)  // 30 pts
{
	/*
		..........
	
		Implement the Direct Illumination
		Using Phong Reflection Model here

		..........
	*/
	if (intersection.w == -1) {
		return float4(0, 0, 0, 1);
	}
	float3 N = GetNormal(intersection);
	float3 C = Interpolate(intersection, true);
	float3 pos = Interpolate(intersection, false);
	float3 L = normalize(lightPosition - pos);
	float shadowDecay = lightColor.w * GetShadow(pos, L);
	return float4(lightColor.xyz * C * (dot(L, N) - shadowDecay), 1);
}

float4 Environment(float4 intersection) // 30 pts
{
	/*
		..........
	
		Implement the Global Illumination
		Using Lambert Reflection Model here

		..........
	*/
	float3 color = float3(0, 0, 0);
	if (intersection.w == -1) return float4(1, 1, 1, 1);
	float3 N = GetNormal(intersection);
	float3 pos = Interpolate(intersection, false);
	int a = 10;
	int b = a * 2;
	float du = PI / (a - 1);
	float dv = 2 * PI / (b - 1);
	float zero = 0.2;
	for (uint i = 0; i < a; i++) {
		for (uint j = 0; j < b; j++) {
			float u = i * du;
			float v = j * dv;
			float x = sin(u) * cos(v);
			float y = cos(u);
			float z = sin(u) * sin(v);
			float3 dir = float3(x, y, z);
			float intensity = dot(N, dir);
			if (intensity >= zero) {
				float4 nextIntersection = IntersectTriangles(pos, dir);
				if (nextIntersection.w == -1) continue;
				float3 lightPos = Interpolate(nextIntersection, false);
				float lightDist = distance(lightPos, pos);
				float decay = 1.0 / (lightDist * lightDist + zero);
				color += GetColor(nextIntersection) * intensity * decay;
			}
		}
	}
	return float4(color, 1);
}

//https://stackoverflow.com/questions/4858264/find-the-distance-from-a-3d-point-to-a-line-segment
//https://i.stack.imgur.com/X4FoK.png
float distToSegment(float3 p, float3 a, float3 b) {
	float3 ap = p - a;
	float3 bp = p - b;
	float3 ab = b - a;
	float3 pProjAB = dot(ap, ab) / length(ab);
	return length(pProjAB);
}

float4 StylizedColor(float4 intersection) // 40 pts
{
	/*
		..........
	
		Implement a novel lighting model or 
		stylized rendering model as here, 
		this model has not been covered in leceture 

		..........
	*/
	float distThreshold = 0.025;
	float3 borderColor = float3(0, 0, 0);
	float minDist = MaxDistance;
	if (intersection.w == -1) return float4(borderColor, 0);
	//if (intersection.w < 10) return float4(borderColor, 0); // Stupid way to not display on walls
	int i = intersection.w;
	float3 pos = Interpolate(intersection, false);
	uint i0 = uint(triangles[i].x), i1 = uint(triangles[i].y), i2 = uint(triangles[i].z);
	minDist = min(minDist, distToSegment(pos, positions[i0].xyz, positions[i1].xyz));
	minDist = min(minDist, distToSegment(pos, positions[i1].xyz, positions[i2].xyz));
	minDist = min(minDist, distToSegment(pos, positions[i2].xyz, positions[i0].xyz));
	minDist = min(minDist, distToSegment(pos, positions[i0].xyz, positions[i2].xyz));
	minDist = min(minDist, distToSegment(pos, positions[i1].xyz, positions[i0].xyz));
	minDist = min(minDist, distToSegment(pos, positions[i2].xyz, positions[i1].xyz));
	if (minDist > distThreshold) return float4(borderColor, 0);

	return float4(borderColor, 1);
}

float4 GetDepthColor(float4 intersection) {
	float3 pos = Interpolate(intersection, false);
	float dist = distance(pos, viewPoint.xyz);
	float gray = pow(3.8 - dist, 0.8) / 1.5;
	return float4(gray, gray, gray, 1);
}

float3 HueColor(float H) {
	float s = 1, v = 1;
	H = frac(H); // Normalize H to the range [0, 1]
	float t = H * 6.0; // Map H to the [0, 6) range
	float f = frac(t); // Get the fractional part of t
	t = floor(t); // Integer part of t
	float l = v * (1 - s);
	float m = v * (1 - s * f);
	float n = v * (1 - s * (1 - f));
	if (t < 1)
		return float3(v, n, l);
	else if (t < 2)
		return float3(m, v, l);
	else if (t < 3)
		return float3(l, v, n);
	else if (t < 4)
		return float3(l, m, v);
	else if (t < 5)
		return float3(n, l, v);
	else
		return float3(v, l, m);
}

float4 GetHSVColor(float4 intersection) {
	float3 pos = Interpolate(intersection, false);
	float dist = distance(pos, viewPoint.xyz);
	float hue = pow(3.8 - dist, 0.8) / 1.5;
	return float4(HueColor(1 - hue), 1);
}

float3 OffsetEyeCenter(float2 offset) {
	// Calculate the eye center offset in 3D space
	float3 offsetEyeCenter = viewPoint + offset.x * rightDirection + offset.y * upDirection;

	return offsetEyeCenter;
}

float3 OffsetViewDirection(float3 inputPosition, float3 offsetEyeCenter) {
	float focalLength = viewPoint.w;
	float3 focus = viewPoint + focalLength * forwardDirection.xyz;
	float3 rightOffset = inputPosition.x * rightDirection.xyz;
	float3 upOffset = inputPosition.y * upDirection.xyz;
	float3 viewCenter = focus + rightOffset + upOffset;
	
	return normalize(viewCenter - offsetEyeCenter);
}


struct VS_Input
{
	float2 position : POSITION;
};

struct VS_Output
{
	float3 position : POSITION;
	float4 sv_position : SV_POSITION;
};

VS_Output VS_Main(VS_Input input)
{
	VS_Output output; output.position=float3(input.position, 0);
	output.sv_position=float4(output.position, 1); return output;
}

float4 ViewDirectionColor(float3 viewDirection)
{
	float r=dot(viewDirection, rightDirection.xyz);
	float g=dot(viewDirection, upDirection.xyz);
	float b=dot(viewDirection, forwardDirection.xyz);
	return float4((float2(r, g)+float2(1, 1))/2, b, 1);
}

float4 PS_Main(VS_Output output) : SV_TARGET
{
	/*float3 viewDirection=ViewDirection(output.position);
	float4 intersection=IntersectTriangles(viewPoint.xyz, viewDirection);
	return GetHSVColor(intersection);*/
	//float4 intersection = IntersectTriangles(viewPoint.xyz, viewDirection);
	float4 color = float4(0, 0, 0, 0);
	int steps = 5, k = 0;
	float d = 0.004;
	for (int i = -steps; i <= steps; i++) {
		for (int j = -steps; j <= steps; j++, k++) {
			float3 eyeCenter = OffsetEyeCenter(float2(i * d, j * d));
			float3 viewDirection = OffsetViewDirection(output.position, eyeCenter);
			color += GetColor(IntersectTriangles(eyeCenter, viewDirection));
		}
	}
	return color / k;
}