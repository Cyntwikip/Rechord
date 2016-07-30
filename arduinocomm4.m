%(c) Jude Teves

clear; clc;

%Arduino Interface 4 code

%prints info about ports available
instrhwinfo('serial')

try     
    s = serial('COM9');
    %set(s, 'Terminator', 'LF'); % Default terminator is \n
    set(s,'BaudRate',115200);
    set(s,'DataBits', 8);
    set(s,'StopBits', 1);
    set(s,'Timeout', 3);
    set(s,'InputBufferSize', 65000);
%     s = serial('COM9', 'Baudrate', 57600);
    fopen(s);
    pause(2);
    s.ReadAsyncMode = 'continuous';
    %s.ReadAsyncMode = 'manual';
    
    % Various variables
    numberOfDatas = 2048;
    str1 = zeros(1, numberOfDatas);
    str2 = zeros(1, numberOfDatas);
    str3 = zeros(1, numberOfDatas);
    str4 = zeros(1, numberOfDatas);
    str5 = zeros(1, numberOfDatas);
    str6 = zeros(1, numberOfDatas);
    
    % Start asynchronous reading
    readasync(s);   
    
    for counter=1:1
        
        fprintf(s,'c');
        disp(datestr(now, 'HH:MM:SS:FFF'));
        fprintf(1,'done writing\n');
        
        str1 = fread(s, numberOfDatas, 'uint8');
        str2 = fread(s, numberOfDatas, 'uint8');
        str3 = fread(s, numberOfDatas, 'uint8');
        str4 = fread(s, numberOfDatas, 'uint8');
        str5 = fread(s, numberOfDatas, 'uint8');
        str6 = fread(s, numberOfDatas, 'uint8');
        
        disp(datestr(now, 'HH:MM:SS:FFF'));
        
%         N = 2048;
%         ts = 0.0005;
%         t = ts*(0:N-1);
%         wavefft = abs(fft(data));
%         ft = 0:ts:ts*(N-1);
%         wavelen = length(wavefft)/2;
%         wave = wavefft(1:wavelen);
%         [val index] = max(wave);
%         
%         fs = 1/ts;
%         freq = index*fs/N
        
    end
 
    % Give the external device some time…
    pause(3);
    
    stopasync(s);
    fclose(s);

catch
    %s.BytesAvailable
    fprintf(1, 'Error! Closing serial port\n');
    stopasync(s);
    fclose(s);
    
end

