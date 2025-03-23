FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive 

RUN apt-get update && \
    apt-get install -y --no-install-recommends ucspi-tcp && \
    rm -rf /var/lib/apt/lists/*
RUN     useradd ctf

WORKDIR /home/ctf

COPY chall      /home/ctf/
COPY run.sh     /home/ctf/
ENV FLAG "flag{prolly_still_quite_easy}"
RUN echo $FLAG > /home/ctf/flag.txt

RUN chown -R root:root  /home/ctf
RUN chmod -R 755        /home/ctf

EXPOSE 1337
ENTRYPOINT ["tcpserver", "0.0.0.0", "1337", "./run.sh"]