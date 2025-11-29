import torch

class InferenceModel():
    def __init__(self, model_path):
        self.model = torch.load(model_path)
        self.model.eval()

    def run(self, input_tensor):
        # input_tensor = torch.from_numpy
        input_tensor = input_tensor.unsqueeze(0)

        with torch.no_grad():
            output_tensor = self.model(input_tensor)

        action = output_tensor.squeeze(0).cpu().numpy()
        
        return action