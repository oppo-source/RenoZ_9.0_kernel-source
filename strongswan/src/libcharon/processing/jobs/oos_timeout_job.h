/*
 * Copyright (C) 2006 Tobias Brunner, Daniel Roethlisberger
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

/**
 * @defgroup oos_timeout_job oos_timeout_job
 * @{ @ingroup cjobs
 */

#ifndef OOS_TIMEOUT_JOB_H_
#define OOS_TIMEOUT_JOB_H_

typedef struct oos_timeout_job_t oos_timeout_job_t;

#include <library.h>
#include <processing/jobs/job.h>
#include <sa/ike_sa_id.h>

/**
 * Class representing a OOS_TIMEOUT Job.
 *
 * Job to periodically send a OOS timeout event,
 */
struct oos_timeout_job_t {
	/**
	 * implements job_t interface
	 */
	job_t job_interface;
};

/**
 * Creates a job of type OOS_TIMEOUT.
 *
 * @param ike_sa_id		identification of the ike_sa as ike_sa_id_t object (gets cloned)
 * @param oos_seq_num		OOS sequence number
 * @param extended		OOS timeout already extended
 * @return				initiate_ike_sa_job_t object
 */
oos_timeout_job_t *oos_timeout_job_create(ike_sa_id_t *ike_sa_id, u_int32_t oos_seq_num, bool extended);

#endif /** OOS_TIMEOUT_JOB_H_ @}*/
