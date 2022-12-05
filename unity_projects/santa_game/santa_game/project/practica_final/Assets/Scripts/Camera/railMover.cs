using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class railMover : MonoBehaviour
{
    public rail rail;
    public Transform follow;
    public Transform lookAt;
    public bool smothMove = true;
    [SerializeField]
    private float moveSpeed = 5.0f;
    private Transform thistransform;
    private Vector3 lastPosition;
    public float max_distance;
    private void Start()
    {
        thistransform = transform;
        lastPosition = thistransform.position;
    }
    private void Update()
    {

        if (smothMove)
        {
            lastPosition = Vector3.Lerp(lastPosition, rail.ProjectedPositionOnRail(follow.position), Time.deltaTime*moveSpeed);
            thistransform.position = lastPosition;
        }
        else
        {
            thistransform.position = rail.ProjectedPositionOnRail(follow.position);
        }
        float dist = Vector3.Distance(transform.position, follow.position);
        
        //if (dist > max_distance) { Vector3 dist_vector = transform.position - lookAt.position; transform.Translate(dist_vector.normalized*10); }
        thistransform.LookAt(lookAt.position);
    }
}
