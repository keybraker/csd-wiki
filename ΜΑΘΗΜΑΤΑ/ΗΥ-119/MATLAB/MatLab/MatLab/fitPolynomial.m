function [ a ] = fitPolynomial(x,y)
    for i=1:size(x);
        for j=1:size(x);
            if(j==length(x))
                a(i,j)=1;
            else
                a(i,j) = x(i).^(length(x)-j);
            end
        end
    end
    w=inv(a)*y
end
%size(); gia tis diastaseis toy pinaka
%kataskeyazw n-poluwnumo
%if(); gemizei me asoys thn teleytaia sthlh toy pinaka
%lynw grammiko systhma