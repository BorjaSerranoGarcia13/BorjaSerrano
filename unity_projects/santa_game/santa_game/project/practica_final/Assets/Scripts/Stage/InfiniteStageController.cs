using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InfiniteStageController : MonoBehaviour {

    public GameObject player;
    public GameObject compacter;
    private StageGenerator generator;

    // Start is called before the first frame update
    void Start() {
        generator = GetComponent<StageGenerator>();
        player.GetComponent<SpawnPoint>().OnPlayerReachedSpawnPoint += PlayerReachedSpawnPointHandler;
        compacter.GetComponent<Compacter>().OnEnvairomentCompacted += EnvairomentCompactedHandler;
    }

    void OnEnabled() {
        player.GetComponent<SpawnPoint>().OnPlayerReachedSpawnPoint += PlayerReachedSpawnPointHandler;
        compacter.GetComponent<Compacter>().OnEnvairomentCompacted += EnvairomentCompactedHandler;
    }

    void OnDisabled() {
        player.GetComponent<SpawnPoint>().OnPlayerReachedSpawnPoint -= PlayerReachedSpawnPointHandler;
        compacter.GetComponent<Compacter>().OnEnvairomentCompacted -= EnvairomentCompactedHandler;
    }

    // Update is called once per frame
    void Update()
    {

    }

    private void PlayerReachedSpawnPointHandler(Transform spawnPointTransform) {
        generator.Generate(generator.distanceBetweenSpawns);
    }

    private void EnvairomentCompactedHandler(GameObject envairoment) {
        // TODO: Do something cool

        if (!envairoment.CompareTag("Player")) {
            Destroy(envairoment);
        }
    }
}
