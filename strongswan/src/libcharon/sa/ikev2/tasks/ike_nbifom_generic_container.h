/*
 * add by shailendra
 */

/**
 * @defgroup nbifom_generic_container
 * @{ @ingroup tasks_v2
 */

#ifndef IKE_NBIFOM_GENERIC_CONTAINER_H
#define IKE_NBIFOM_GENERIC_CONTAINER_H

typedef struct ike_nbifom_generic_container_t ike_nbifom_generic_container_t;

#include <library.h>
#include <sa/ike_sa.h>
#include <sa/task.h>


/**
 * Task of type ike_nbifom_generic_container.
 */
struct ike_nbifom_generic_container_t {

	/**
	 * Implements the task_t interface
	 */
	task_t task;
};


/**
 * Create a new ike_nbifom_generic_container_t task.
 *
 * @param ike_sa		IKE_SA this task works for
 * @param initiator		TRUE if we initiate the delete
 * @return				ike_nbifom_generic_container task to handle by the task_manager
 */
ike_nbifom_generic_container_t *ike_nbifom_generic_container_create(ike_sa_t *ike_sa, bool initiator);

#endif

