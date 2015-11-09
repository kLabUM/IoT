s = serial('/dev/cu.USA19Hfd12P1.1');
fopen(s);
% TX Data
txdata = {'00' '61' 'FF' '18' '24' '10'};

% Convert to Decimal Format
txdata_dec = hex2dec(txdata);

% Write using the UINT8 data format
fwrite(s,txdata_dec);

% Read back data 
rxdata = [char(fread(s))]'

fclose(s);
delete(s)
clear s
