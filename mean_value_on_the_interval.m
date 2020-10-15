clear;
k = 25;
mat = load ('vrijed_mat');
z = 1;
for i = k:k:size(mat,1)
    s1=0;
    s2=0;
    s3=0;
    for j = 1:k-1
        s1=s1+mat(i-j,1);
        s2=s2+mat(i-j,2);
        s3=s3+mat(i-j,3);
    end
    s1=s1/(k-1);
    s2=s2/(k-1);
    s3=s3/(k-1);    
    x1(z) = (5/1000)*s1;
    x2(z) = (5/1000)*s2;
    x3(z) = (5/1000)*s3;
    z = z+1;
end
t = [0:1:(size(mat,1))/k-1];
plot(t, x1, 'b', t, x2, 'r', t, x3, 'g');
title('Odziv uslijed promjene smjera vrtnje');
xlabel('Vrijeme t [s]');
ylabel('Naponi U [V]');
legend('Napon potenciometra','Napon tahogeneratora','Izlazna vrijednost PID funkcije');
