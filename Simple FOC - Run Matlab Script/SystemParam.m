
open_system("SimpleFOC.slx") 

%% Motor Parameters
bldc.model  = 'Multi-star';   % Motor           
bldc.p      = 6;                % Pole Pairs           
bldc.Rs     = 0.36;             % Stator Resistance (ohms)       
bldc.Ld     = 0.2e-3;           % D-axis inductance (H)        
bldc.Lq     = 0.4e-3;           % Q-axis inductance (H)         
bldc.J      = 10.061551833333e-4;% Inertia (Kg-m2)      
bldc.B      = 2.636875217824e-6;% Kg-m2/s    
bldc.Ke     = 4.64;             % Bemf Const	
bldc.Kt     = 0.274;            % Nm/A       
bldc.I_rated= 26;              % Max Current Is (A)      	
bldc.N_max  = 6000;             % Max Speed (RPM)                 
bldc.FluxPM     = (bldc.Ke)/(sqrt(3)*2*pi*1000*bldc.p/60); % (Wb) 
bldc.T_rated    = (3/2)*bldc.p*bldc.FluxPM*bldc.I_rated; % Max Torque (Nm)
bldc.Voltage = 16;

%% Intial Values

% Motor Intial Parameters
Initial.bldc.ILd = 0;
Initial.bldc.ILq = 0;
Initial.bldc.ITheta = 0;

% Input
Initial.Speed = 1000;
Initial.Torque = 0;
Initial.Id = 0;
Initial.Iq = 5;

Initial.InverterVoltage = 12;

QuadratureCurrentSelect = 0; % 0 = Iq Setpoint | 1 = Speed Setpoint

%% PWM Switching frequency
PWM_frequency 	= 20e3;    
T_pwm           = 1/PWM_frequency;  

%% Sampling Time
Ts          	= T_pwm;            
Ts_simulink     = T_pwm/20;          
Ts_motor        = T_pwm/20;            
Ts_inverter     = T_pwm/20;             
Ts_speed        = 10*Ts;

%% ControllerGains PI

% Reference: https://e2e.ti.com/blogs_/b/industrial_strength/archive/2015/07/20/teaching-your-pi-controller-to-behave-part-i
BW_hz = 3000; % in Hz
Kp_id = 2*pi*BW_hz*bldc.Ld; 
Ki_id = 2*pi*BW_hz*bldc.Rs*Ts; 
Kp_iq = 2*pi*BW_hz*bldc.Lq; 
Ki_iq = 2*pi*BW_hz*bldc.Rs*Ts; 