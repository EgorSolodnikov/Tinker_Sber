import torch
from src.modules.actor_critic import ActorCriticRMA, ActorCriticMixedBarlowTwins


class InferenceModel():
    def __init__(self, model_path):

        num_prop = 39
        num_scan = 187  
        num_priv_latent = 4 + 1 + 12 + 12 + 12 + 6 + 1 + 4 + 1 - 3 + 4 - 10  # = 48
        num_hist = 10
        num_actions = 10
        num_costs = 5
        
        policy_cfg = {
            'scan_encoder_dims': None,
            'actor_hidden_dims': [512, 256, 128],
            'critic_hidden_dims': [512, 256, 128],
            'priv_encoder_dims': [],
            'activation': 'elu',
            'teacher_act': False,
            'imi_flag': False,
            'num_costs': num_costs
        }
        
        self.model = ActorCriticMixedBarlowTwins(
            num_prop=num_prop,
            num_scan=num_scan,
            num_critic_obs=num_prop + num_scan + num_priv_latent + num_hist*num_prop,
            num_priv_latent=num_priv_latent,
            num_hist=num_hist,
            num_actions=num_actions,
            init_noise_std=1.0,
            **policy_cfg
        )

        checkpoint = torch.load(model_path, map_location='cpu')
        self.model.load_state_dict(checkpoint['model_state_dict'])
        self.model.eval()

    def run(self, input_tensor: torch.Tensor):
        # input_tensor = torch.from_numpy
        # input_tensor = input_tensor.unsqueeze(0)

        with torch.no_grad():
            output_tensor = self.model.act_teacher(input_tensor)

        action = output_tensor.squeeze(0).cpu().numpy()
        
        return action