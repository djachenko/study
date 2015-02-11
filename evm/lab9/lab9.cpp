#include <iostream>
#include <libusb.h>
#include <stdio.h>

using namespace std;

void printdev(libusb_device *dev)
{
	libusb_device_descriptor desc;/* дескриптор устройства */
	libusb_config_descriptor *config;/* дескриптор конфигурации объекта */

	const libusb_interface *inter;
	const libusb_interface_descriptor *interdesc;
	const libusb_endpoint_descriptor *epdesc;

	int r = libusb_get_device_descriptor(dev, &desc);

	if (r < 0)
	{
		fprintf(stderr, "Ошибка: дескриптор устройства не получен, код: %d.\n",r);

		return;
	}

	libusb_get_config_descriptor(dev, 0, &config);/* получить конфигурацию устройства */

	printf("количество возможных конфигураций: %.2d\n", (int)desc.bNumConfigurations);
	printf("класс устройства: %.2d\n", (int)desc.bNumConfigurations);
	printf("идентификатор производителя %.4x\n", desc.idVendor);
	printf("идентификатор устройства %.2x\n", desc.idProduct);
	printf("количество интерфейсов %.3d\n", (int)config->bNumInterfaces );

	for(int i=0; i<(int)config->bNumInterfaces; i++)
	{
		inter = &config->interface[i];

		printf("количество альтернативных настроек %.2d\n", inter->num_altsetting);
		printf("класс устройства: %.2X\n", (int)desc.bDeviceClass );

		for(int j=0; j<inter->num_altsetting; j++)
		{
			interdesc = &inter->altsetting[j];

			printf("	номер интерфейса %.2d\n", (int)interdesc->bInterfaceNumber);
			printf("	количество конечных точек %.2d\n", (int)interdesc->bNumEndpoints );

			for(int k=0; k<(int)interdesc->bNumEndpoints; k++)
			{
				epdesc = &interdesc->endpoint[k];

				printf("		тип дескриптора %.2d\n", (int)epdesc->bDescriptorType);
				printf("		адрес конечной точки %.9d\n", (int)(int)epdesc->bEndpointAddress );
			}
		}
	}

	printf("===========================================================\n");

	libusb_free_config_descriptor(config);
}

int main()
{
	libusb_device **devs; /* указатель на указатель на устройство, */
	/* используется для получения списка */
	/* устройств */

	libusb_context *ctx = NULL; /* контекст сессии libusb */

	int r; /* для возвращаемых значений */
	ssize_t cnt; /* число найденных USB устройств */
	ssize_t i; /* индексная переменная цикла перебора */
	/* всех устройств */

	r = libusb_init(&ctx); /* инициализировать библиотеку libusb, */
	/* открыть сессию работы с libusb */

	if(r < 0)
	{
		fprintf(stderr, "Ошибка: инициализация не выполнена, код: %d.\n", r);
		return 1;
	}

	libusb_set_debug(ctx, 3); /* задать уровень подробности отладочных */
	/* сообщений */

	cnt = libusb_get_device_list(ctx, &devs);
	/* получить список всех найденных USB */
	/* устройств */

	if(cnt < 0)
	{
		fprintf(stderr, "Ошибка: список USB устройств не получен.\n", r);
		return 1;
	}

	for(i = 0; i < cnt; i++)
	{ /* цикл перебора всех устройств */
		printdev(devs[i]); /* печать параметров устройства */
	}

	libusb_free_device_list(devs, 1);
	/* освободить память, выделенную */
	/* функцией получения списка устройств */

	libusb_exit(ctx); /* завершить работу с библиотекой libusb, */
	/* закрыть сессию работы с libusb */

	return 0;
}
