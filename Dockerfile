FROM debian:stable

RUN apt-get update -yqq && apt-get install -yqq \
    grub-efi-amd64-bin \
    dosfstools \
    xorriso \
    mtools \
    grub-pc-bin

WORKDIR /app

CMD ["./grub.sh"]
