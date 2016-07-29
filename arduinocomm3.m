
%(c) Jude Teves

clear; clc;

%Arduino Interface 3 code

%prints info about ports available
instrhwinfo('serial')

try 
    
    s = serial('COM9');
    %set(s, 'Terminator', 'LF'); % Default terminator is \n
    %fprintf(1,'terminator\n');
    %set(s,'BaudRate', 57600);
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
    %numberOfDatas = 50;
    numberOfDatas = 2048;
    %data = zeros(1, numberOfDatas);
    str1 = zeros(1, numberOfDatas);
    str2 = zeros(1, numberOfDatas);
    
    % Start asynchronous reading
    readasync(s);   
    
    for counter=1:1
        
        fprintf(s,'c');
        disp(datestr(now, 'HH:MM:SS:FFF'));
        fprintf(1,'done writing\n');
        
        str1 = fscanf(s, '%u', numberOfDatas);
        str2 = fscanf(s, '%u', numberOfDatas);
        
        %for counter2=1:numberOfDatas
            % Get the data from the serial object
            %str1(counter2) = fscanf(s, '%u');
            %DISCOVERY!! fscanf looks for terminating character. fread does
            %not.
            
            %data(counter2) = fread(s,1,'uint8');
            %fprintf(1,data(counter2)); fprintf(1,'\n');
        %end
        
        %for counter2=1:numberOfDatas
            % Get the data from the serial object
            %str2(counter2) = fscanf(s, '%u');
            %DISCOVERY!! fscanf looks for terminating character. fread does
            %not.
            
            %data(counter2) = fread(s,1,'uint8');
            %fprintf(1,data(counter2)); fprintf(1,'\n');
        %end
        
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

