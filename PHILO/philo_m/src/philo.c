#include "../inc/philo.h"

int	main(int argc, char *argv[])
{
	int				number_of_philo;
	t_dinning		*dinning;
	t_philosopher	*philosopher;

	dinning = create_dinning(argc, argv);
	if(!dinning)
		return(printf("Error.\n"));
	philosopher = NULL;
	number_of_philo = 0;
	while (number_of_philo++ < dinning->options[num_of_philosophers])
	{	
		new_philosopher(number_of_philo - 1, dinning, &philosopher);
		pthread_create(&(philosopher->philo_id), NULL, &routine, philosopher);
		pthread_create(&(philosopher->death_id), NULL, &check_death,
			philosopher);
	}
	number_of_philo = 0;
	while (number_of_philo++ < dinning->options[num_of_philosophers])
	{
		pthread_join(philosopher->philo_id, NULL);
		pthread_join(philosopher->death_id, NULL);
	}
	free(dinning);
	return (0);
}
