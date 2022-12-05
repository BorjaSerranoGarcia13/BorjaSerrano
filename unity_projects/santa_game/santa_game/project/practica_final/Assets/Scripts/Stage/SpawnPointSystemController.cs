using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnPointSystemController : MonoBehaviour {

    public Transform currentSpawnPoint;
    public GameObject player;

    // Start is called before the first frame update
    private void Start() {
        player.GetComponent<SpawnPoint>().OnPlayerReachedSpawnPoint += PlayerReachedSpawnPointHandler;
        player.GetComponent<LifeController>().OnDamageTaken += Spawn;
    }

    private void OnDisabled() {
        player.GetComponent<SpawnPoint>().OnPlayerReachedSpawnPoint -= PlayerReachedSpawnPointHandler;
        player.GetComponent<LifeController>().OnDamageTaken -= Spawn;
    }

    private void OnEnabled() {
        player.GetComponent<SpawnPoint>().OnPlayerReachedSpawnPoint += PlayerReachedSpawnPointHandler;
        player.GetComponent<LifeController>().OnDamageTaken += Spawn;
    }

    private void PlayerReachedSpawnPointHandler(Transform spawnPointTransform) {
        currentSpawnPoint = spawnPointTransform;
    }

    public void Spawn(int life, int damage) {
        if (currentSpawnPoint != null) {
            player.transform.position = currentSpawnPoint.position;
            player.transform.rotation = currentSpawnPoint.rotation;
        } else {
            player.SetActive(false);
        }
    }

}
